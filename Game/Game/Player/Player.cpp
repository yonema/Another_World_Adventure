#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

#ifdef _DEBUG
#include "../Monster/Monster.h"
#endif

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/player.fbx";	//プレイヤーモデルのファイルパス
		constexpr float kPlayerModelScale = 0.1f;	//プレイヤーモデルの拡大率
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::StartSub() {

			//アニメーションを初期化。
			m_animation.Init();

			//プレイヤーモデルを生成。
			CreatePlayerModel();

			//アニメーションに使用するモデルを伝える。
			m_animation.SetPlayerModel(m_modelRenderer);

			//武器を生成。
			CreateWeapon();

			//防具を生成。
			CreateArmor();

			//ステータスを初期化。
			m_status.Init();

			//入力クラスを初期化。
			m_input.Init(&m_action, &m_animation);

			//アクションクラスを初期化。
			m_action.Init(&m_status, GetItemManager());

			m_fontRenderer = NewGO<nsGraphics::nsFonts::CFontRenderer>();

#ifdef _DEBUG
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
			return true;
		}

		void CPlayer::OnDestroySub() {

			//プレイヤーモデルを破棄。
			DeleteGO(m_modelRenderer);

			//武器を破棄。
			if (m_weapon != nullptr) {
				m_weapon->Release();
				m_weapon = nullptr;
			}
		}

		void CPlayer::UpdateActor(float deltaTime) {

			//プレイヤーアクションクラスを更新。
			m_action.Update(deltaTime);

			//入力クラスを更新。
			m_input.Update(m_modelRenderer->IsPlaying());

			//アニメーションを更新。
			m_animation.Update();

			//座標を設定。
			m_modelRenderer->SetPosition(m_action.GetPosition());

			//回転情報を設定。
			m_modelRenderer->SetRotation(m_action.GetRotation());

#ifdef _DEBUG
			//プレイヤーのHPを表示。
			size_t dispTextSize = sizeof(wchar_t) * static_cast<size_t>(32);
			StringCbPrintf(m_dispText, dispTextSize, L"HP = %3.4f", m_status.GetHP());
			m_fontRenderer->SetText(m_dispText);
#endif
		}

		void CPlayer::ApplyDamage(float power, bool canGuard) {

			//ガード中かつガードゲージの値が威力より高い。
			if (m_action.GetState() == EnPlayerState::enGuard
				&& canGuard == true
				&& m_status.GetGuardGaugeValue() >= power
				)
			{
				//ガード成功。
				//威力分だけガードゲージの値が減少する。
				m_status.DamageGuardGaugeValue(power);
			}
			else {
				//ダメージをくらう。
				m_status.DamageHP(power);
				m_action.SetState(EnPlayerState::enDamage);
			}
		}

		void CPlayer::SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill) {

			//アクティブスキルを設定。
			m_action.SetActiveSkill(activeSkillNum, activeSkill);
		}

		void CPlayer::CreatePlayerModel() {

			//プレイヤーモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//プレイヤーモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationZ(nsMath::YM_PI);

			//アニメーションのデータを定義。
			const char* animFilePath[static_cast<int>(nsPlayerAnimation::CPlayerAnimation::EnAnimName::enNum)];

			//アニメーションの数だけまわす。
			for (int animIndex = 0; animIndex < static_cast<int>(nsPlayerAnimation::CPlayerAnimation::EnAnimName::enNum); animIndex++) {

				//アニメーションを取り出し、格納。
				animFilePath[animIndex] = m_animation.GetAnimFilePath()[animIndex];
			}

			//アニメーションのデータを生成。
			SAnimationInitData* animData = new SAnimationInitData(
				static_cast<unsigned int>(nsPlayerAnimation::CPlayerAnimation::EnAnimName::enNum),
				animFilePath
			);
			
			//アニメーションを初期化。
			modelInitData.animInitData = animData;

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
			return m_weapon;
		}

		nsArmor::CArmor* CPlayer::GetArmor() {

			//防具を受け取る。
			return m_armor;
		}

		void CPlayer::CreateWeapon() {

#ifdef _DEBUG
			////武器情報を定義。
			//nsWeapon::SWeaponInfo weaponInfo;
			//weaponInfo.attack = 100;
			//weaponInfo.intelligence = 100;
			//weaponInfo.critical = 10;
			//weaponInfo.weaponType = nsWeapon::EnWeaponType::enSword;
			//weaponInfo.name = "NewSword";
			//
			////武器モデルのファイルパスを定義。
			//const char* weaponModelFilePath = "Assets/Models/sampleBox.fbx";
			//
			////武器生成クラスを使って武器を生成。
			//nsWeapon::CWeaponBuilder weaponBuilder;
			//m_weapon = weaponBuilder.Create(weaponInfo, weaponModelFilePath);
#endif
		}

		void CPlayer::CreateArmor() {

		}
	}
}

