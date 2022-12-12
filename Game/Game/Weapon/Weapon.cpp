#include "YonemaEnginePreCompile.h"
#include "Weapon.h"

namespace nsAWA {

	namespace nsWeapon {

		void CWeapon::Create(const SWeaponInfo& weaponInfo, const char* modelFilePath) {

			//武器モデルを生成。
			CreateModel(modelFilePath);

			//武器情報を設定。
			m_sInfo = weaponInfo;
		}

		void CWeapon::Release() {

			//武器モデルを破棄。
			DeleteGO(m_modelRenderer);

			//自身を破棄。
			delete this;
		}

		void CWeapon::CreateModel(const char* modelFilePath) {

			//武器モデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//武器モデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = modelFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//武器モデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CWeapon* CWeaponBuilder::Create(const SWeaponInfo& weaponInfo, const char* modelFilePath) {

			//武器を生成。
			CWeapon* weapon = new CWeapon;
			weapon->Create(weaponInfo, modelFilePath);

			//生成された武器を返す。
			return weapon;
		}
	}
}
