#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Skill/ActiveSkillList.h"
#include "../UserData.h"

#ifdef _DEBUG
#include "../Monster/Monster.h"
#include "PlayerManager.h"
#endif
#include "../UI/Battle/Player/PlayerBattleStatusUI.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/player.fbx";	//プレイヤーモデルのファイルパス
		constexpr float kPlayerModelScale = 0.1f;	//プレイヤーモデルの拡大率
		constexpr const char* const kPlayerModelTextureRootPath = "player";	//プレイヤーモデルのテクスチャのパス
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::StartSub() {

			//プレイヤー管理クラスに自身を設定。
			CPlayerManager::GetInstance()->SetPlayer(this);

			//アニメーションを初期化。
			m_animation.Init(this, &m_input, &m_action);

			//プレイヤーモデルを生成。
			CreatePlayerModel();

			//アニメーションに使用するモデルを伝える。
			m_animation.SetPlayerModelAndAnimEvent(m_modelRenderer);

			//武器管理クラスを初期化。
			m_weaponManager.Init(m_modelRenderer);

#ifdef _DEBUG
			//武器を設定。
			CPlayerManager playerManager;
			if (playerManager.FindPlayer()) {

				playerManager.SetWeapon("NewSword");
				playerManager.SetArmor("NewArmor");
			}

#endif // DEBUG

			//ステータスを初期化。
			m_status.Init();

			//入力クラスを初期化。
			m_input.Init(&m_action, &m_animation);

			//アクションクラスを初期化。
			m_action.Init(m_position, m_rotation, &m_status, GetFeatureManager(),&m_animation);

			//当たり判定を初期化。
			m_collider.Init(this);

#ifdef _DEBUG
			m_fontRenderer = NewGO<nsGraphics::nsFonts::CFontRenderer>();

			//フォントの情報を設定。
			nsGraphics::nsFonts::CFontRenderer::SFontParameter fontParam(
				L"",
				{0.0f,20.0f},
				nsMath::CVector4::White(),
				0.0f,
				0.5f,
				nsMath::CVector2::Zero(),
				EnAnchors::enTopLeft
			);

			//初期化。
			m_fontRenderer->Init(fontParam);
#endif

			// UIの処理
			m_playerBattleStatusUI = NewGO<nsUI::CPlayerBattleStatusUI>();
			m_playerBattleStatusUI->LoadLevel();


			//データをロード。
			CUserData userData;
			userData.Load();


			return true;
		}

		void CPlayer::OnDestroySub() {

			//プレイヤーモデルを破棄。
			DeleteGO(m_modelRenderer);

			//アニメーションを破棄。
			m_animation.Release();

			//武器を破棄。
			m_weaponManager.Release();

			//防具を破棄。
			if (m_armor != nullptr) {
				m_armor->Release();
				m_armor = nullptr;
			}

			//当たり判定を破棄。
			m_collider.Release();

			// UIを破棄。
			DeleteGO(m_playerBattleStatusUI);
		}

		void CPlayer::UpdateActor(float deltaTime) {

			//死んでいるなら。
			if (IsDeath()) {

				//死亡状態に。
				m_action.SetState(EnPlayerState::enDeath);

				//アニメーションを更新。
				m_animation.Update(m_action.IsChangeState(), m_action.GetState());

				//ステートの変更状況を初期化。
				m_action.ResetChangeState();

				//コライダーを破棄。
				if (!m_collider.IsReleased()) {

					m_collider.Release();
				}

				//これ以上は何もせず終了。
				return;
			}

			//入力クラスを更新。
			m_input.Update(m_modelRenderer->IsPlaying());

			//プレイヤーアクションクラスを更新。
			m_action.Update(deltaTime);

			//アニメーションを更新。
			m_animation.Update(m_action.IsChangeState(), m_action.GetState());

			//ステートの変更状況を初期化。
			m_action.ResetChangeState();

			//武器管理クラスを更新。
			m_weaponManager.Update();

			//トリガーを更新。
			m_collider.Update();

#ifdef _DEBUG
			//プレイヤーのHPを表示。
			auto itemManager = CPlayerManager::GetInstance()->GetItemManager();

			size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			StringCbPrintf(m_dispText, dispTextSize, L"Item = %s %d", nsUtils::GetWideStringFromString(itemManager->GetItemName()).c_str(), itemManager->GetItemNum());
			m_fontRenderer->SetText(m_dispText);
#endif
		}

		void CPlayer::ApplyDamage(float damage, float power, bool canGuard) {

			//ガード中かつガードできる攻撃なら。
			if (m_action.GetState() == EnPlayerState::enGuard
				&& canGuard == true
				)
			{
				//ガード成功。
				//威力分だけガードゲージの値が減少する。
				m_status.DamageGuardGaugeValue(power);

				//ガードゲージが0になったら。
				if (fabsf(m_status.GetGuardGaugeValue()) < FLT_EPSILON) {
					
					//スタン状態にする。
					m_action.SetState(EnPlayerState::enStun);
				}
			}
			else {
				//ダメージをくらう。
				m_status.DamageHP(damage);

				//ひるみ値を加算。
				m_status.AddWinceValue(damage);

				//ひるみ値がひるみ値の区切りを超えていたら。
				if (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

					//ダメージ状態に設定。
					m_action.SetState(EnPlayerState::enDamage);

					//クールタイムをONに設定。
					m_input.CoolTimeOn();

					//一回ひるんだので、二回以上のひるみは無効とする。
					while (m_status.GetWinceValue() >= m_status.GetWinceDelimiter()) {

						//ひるみ値を減算。
						m_status.SubWinceValue(m_status.GetWinceDelimiter());
					}
				}
			}
		}

		void CPlayer::SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill) {

			//アクティブスキルを設定。
			m_action.SetActiveSkill(setNum, activeSkill);
		}

		nsSkill::CActiveSkill* CPlayer::GetActiveSkill(int skillNum)const {

			//アクティブスキルを取得。
			return m_action.GetActiveSkill(skillNum);
		}

		void CPlayer::SetWeapon(nsWeapon::CWeapon* weapon) {

			//武器を設定。
			m_weaponManager.ChangeWeapon(weapon);
		}

		void CPlayer::SetArmor(nsArmor::CArmor* armor) {

			//既に防具情報が入っていたら。
			if (m_armor != nullptr) {

				//防具を破棄。
				m_armor->Release();
				m_armor = nullptr;
			}

			//防具を設定。
			m_armor = armor;
		}

		void CPlayer::CreatePlayerModel() {

			//プレイヤーモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//プレイヤーモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.textureRootPath = kPlayerModelTextureRootPath;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationZ(nsMath::YM_PI);


			//アニメーションの数を取得。
			const int animNum = static_cast<int>(m_animation.GetAnimFilePath().size());

			//アニメーションのファイルパスの配列を定義。
			std::vector<const char*> animNumVec;

			//アニメーションの数だけ回してファイルパスを格納。
			for (int animIndex = 0; animIndex < animNum; animIndex++) {

				//アニメーションのファイルパスを取得。
				animNumVec.emplace_back(m_animation.GetAnimFilePath()[animIndex].c_str());
			}

			//アニメーションを初期化。
			modelInitData.animInitData.Init(
				static_cast<unsigned int>(animNum),
				animNumVec.data()
			);

			//プレイヤーモデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(kPlayerModelScale);
		}

		CPlayerStatus* CPlayer::GetStatus() {

			//ステータスを受け取る。
			return &m_status;
		}

		nsWeapon::CWeapon* CPlayer::GetWeapon() {

			//武器を受け取る。
			return m_weaponManager.GetWeapon();
		}

		nsArmor::CArmor* CPlayer::GetArmor() {

			//防具を受け取る。
			return m_armor;
		}
	}
}

