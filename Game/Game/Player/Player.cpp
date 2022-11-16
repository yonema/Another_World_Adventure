#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/hoge.fbx";	//プレイヤーモデルのファイルパス
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::Start() {

			//プレイヤーモデルを生成。
			CreatePlayerModel();

			//武器を生成。
			CreateWeapon();

			//ステータスを初期化。
			m_status.Init();

			//入力クラスを初期化。
			m_input.Init(&m_action);

			//アクションクラスを初期化。
			m_action.Init();

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

		void CPlayer::Update(float deltaTime) {

			//プレイヤーアクションクラスを更新。
			m_action.Update(deltaTime);

			//入力クラスを更新。
			m_input.Update();

			//座標を設定。
			m_modelRenderer->SetPosition(m_action.GetPosition());

			//回転情報を設定。
			m_modelRenderer->SetRotation(m_action.GetRotation());
		}

		void CPlayer::ApplyDamage(int power) {

			//ガード中かつガードゲージの値が威力より高い。
			if (m_action.GetState() == EnPlayerState::enGuard
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

		void CPlayer::CreatePlayerModel() {

			//プレイヤーモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//プレイヤーモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.AddRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);

			//プレイヤーモデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(10.0f);
		}

		void CPlayer::CreateWeapon() {

#ifdef _DEBUG

			//武器情報を定義。
			nsWeapon::SWeaponInfo weaponInfo;
			weaponInfo.name = "sampleWeapon";
			weaponInfo.weaponType = nsWeapon::EnWeaponType::enSword;
			weaponInfo.attack = 100;
			weaponInfo.intelligence = 20;
			weaponInfo.critical = 10;

			//武器モデルのファイルパスを定義。（今回はサンプルボックスを使用...）
			const char* weaponModelFilePath = "Assets/Models/sampleBox.fbx";

			//武器生成クラスを使って武器を生成。
			nsWeapon::CWeaponBuilder weaponBuilder;
			m_weapon = weaponBuilder.Create(weaponInfo, weaponModelFilePath);
#endif
		}
	}
}

