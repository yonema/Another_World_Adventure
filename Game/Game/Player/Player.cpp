#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Skill/ActiveSkillList.h"
#include "../UserData.h"
#include "PlayerManager.h"
#include "../Humans/HumanTable.h"

#ifdef _DEBUG
#include "../Monster/Monster.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/PassiveSkill.h"
#endif
#include "../UI/Battle/Player/PlayerBattleStatusUI.h"
#include "../UI/Battle/Skill/SkillIconUI.h"
#include "../UI/Battle/Item/ItemUI.h"
#include "../UI/Menu/MenuManager.h"

namespace nsAWA {

	namespace {

		//constexpr const char* const kPlayerModelFilePath = "Assets/Models/player.fbx";	//プレイヤーモデルのファイルパス
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



			return true;
		}

		void CPlayer::OnDestroySub() {

			//プレイヤー管理クラスを破棄。
			CPlayerManager::GetInstance()->DeleteInstance();

			//アクションクラスを破棄。
			m_action.Release();

			//入力クラスを破棄。
			m_input.Release();

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
			DeleteGO(m_skillIconUI);
			DeleteGO(m_menuManager);
		}

		void CPlayer::UpdateActor(float deltaTime) {

			if (m_isInited != true)
			{
				InitAfterLoadModel();

				return;
			}

			//死んでいるなら。
			if (IsDeath()) {

				//死亡状態に。
				m_action.SetState(EnPlayerState::enDeath);

				//アニメーションを更新。
				m_animation.Update(m_action.IsChangeState(), m_action.GetState());

				//ステートの変更状況を初期化。
				m_action.ResetChangeState();

				//武器管理クラスを更新。
				m_weaponManager.Update();

				//コライダーを破棄。
				if (!m_collider.IsReleased()) {

					m_collider.Release();
				}

				// UIにプレイヤーのステータスを渡す
				m_playerBattleStatusUI->SetUIPlayerStatus(
					m_status.GetHP(), m_status.GetMaxHP(),
					m_status.GetMP(), m_status.GetMaxMP(),
					m_status.GetSP(), m_status.GetMaxSP()
				);

				//これ以上は何もせず終了。
				return;
			}

			//入力クラスを更新。
			m_input.Update(m_modelRenderer->IsPlaying());

			//プレイヤーアクションクラスを更新。
			m_action.Update(deltaTime);

			//ステータスを更新。
			m_status.Update();

			//アニメーションを更新。
			m_animation.Update(m_action.IsChangeState(), m_action.GetState());

			//ステートの変更状況を初期化。
			m_action.ResetChangeState();

			//武器管理クラスを更新。
			m_weaponManager.Update();

			//トリガーを更新。
			m_collider.Update();

			// UIにプレイヤーのステータスを渡す
			m_playerBattleStatusUI->SetUIPlayerStatus(
				m_status.GetHP(), m_status.GetMaxHP(),
				m_status.GetMP(), m_status.GetMaxMP(),
				m_status.GetSP(), m_status.GetMaxSP()
			);

#ifdef _DEBUG
			//プレイヤーのHPを表示。

			//size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			//StringCbPrintf(m_dispText, dispTextSize, L"Level = %d , Exp = %d", m_status.GetLevel(), m_status.GetExp());
			//m_fontRenderer->SetText(m_dispText);
#endif
		}

		void CPlayer::ApplyDamage(float damage, float power, bool canGuard) {

			//被弾中は被弾しない。
			if (m_action.GetState() == EnPlayerState::enDamage) {

				//終了。
				return;
			}

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
					m_input.InputDisable();

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
			//modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFilePath = nsHumans::g_kNameToModelFilePath.at("Player1");
			//modelInitData.textureRootPath = kPlayerModelTextureRootPath;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationZ(nsMath::YM_PI);
			modelInitData.SetFlags(EnModelInitDataFlags::enCullingOff);
			modelInitData.SetFlags(EnModelInitDataFlags::enLoadingAsynchronous);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterAnimationBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enRegisterTextureBank);
			modelInitData.SetFlags(EnModelInitDataFlags::enShadowCaster);


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


		void CPlayer::InitAfterLoadModel()
		{
			if (m_modelRenderer->IsLoadingAsynchronous())
			{
				return;
			}

			//アニメーションに使用するモデルを伝える。
			m_animation.SetPlayerModelAndAnimEvent(m_modelRenderer);

			//武器管理クラスを初期化。
			m_weaponManager.Init(this, m_modelRenderer, &m_action);

			//ステータスを初期化。
			m_status.Init(m_weaponManager.GetWeaponPointer(), m_armor, GetPassiveSkillManager(), GetFeatureManager());

			//入力クラスを初期化。
			m_input.Init(this, &m_action, &m_animation);

			//アクションクラスを初期化。
			m_action.Init(m_position, m_rotation, &m_status, GetFeatureManager(), &m_animation);

			//当たり判定を初期化。
			m_collider.Init(this);

			// UIの処理
			m_playerBattleStatusUI = NewGO<nsUI::CPlayerBattleStatusUI>();
			m_playerBattleStatusUI->LoadLevel();

			m_skillIconUI = NewGO<nsUI::CSkillIconUI>();
			m_skillIconUI->LoadLevel();

			m_itemUI = NewGO<nsUI::CItemUI>();
			m_itemUI->LoadLevel();


			//プレイヤー管理クラスを初期化。
			CPlayerManager::GetInstance()->Init(this);

			m_menuManager = NewGO<nsUI::CMenuManager>();

			//データをロード。
			CUserData userData;
			userData.Load();

			m_isInited = true;

			return;
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

		////////////////////////////////////////////////////////////
		// UI
		////////////////////////////////////////////////////////////

		void CPlayer::ChangeFromSkillToItemUI()
		{
			m_skillIconUI->DeactiveDrawing();
			m_itemUI->ActiveDrawing();
		}

		void CPlayer::ChangeFromItemToSkillUI()
		{
			m_itemUI->DeactiveDrawing();
			m_skillIconUI->ActiveDrawing();
		}

		void CPlayer::MoveNextItemUI()
		{
			m_itemUI->MoveNextItemUI();
		}

		void CPlayer::MoveBackItemUI()
		{
			m_itemUI->MoveBackItemUI();
		}
	}
}

