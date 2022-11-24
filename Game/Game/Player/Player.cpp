#include "YonemaEnginePreCompile.h"
#include "../Status.h"
#include "Player.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/hoge.fbx";	//プレイヤーモデルのファイルパス
		constexpr float kPlayerModelScale = 10.0f;	//プレイヤーモデルの拡大率
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::Start() {

			//プレイヤーモデルを生成。
			CreatePlayerModel();

			//武器を生成。
			CreateWeapon();

			//防具を生成。
			CreateArmor();

			//ステータスを初期化。
			m_status.Init();

			//入力クラスを初期化。
			m_input.Init(&m_action);

			//アクションクラスを初期化。
			m_action.Init();

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

		void CPlayer::OnDestroy() {

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
			m_input.Update();

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


		}

		void CPlayer::CreateArmor() {

#ifdef _DEBUG

			//防具情報を定義。
			nsArmor::SArmorInfo armorInfo;
			armorInfo.name = "sampleArmor";
			armorInfo.defence= 100.0f;
			armorInfo.mind = 20.0f;

			//防具モデルのファイルパスを定義。（今回はサンプルボックスを使用...）
			const char* armorModelFilePath = "Assets/Models/sampleBox.fbx";

			//防具生成クラスを使って武器を生成。
			nsArmor::CArmorBuilder armorBuilder;
			m_armor = armorBuilder.Create(armorInfo, armorModelFilePath);
#endif
		}
	}
}

