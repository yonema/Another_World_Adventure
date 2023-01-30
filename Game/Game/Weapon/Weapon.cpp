#include "YonemaEnginePreCompile.h"
#include "Weapon.h"
#include "WeaponList.h"

namespace nsAWA {

	namespace nsWeapon {

		void CWeapon::Create(const SWeaponInfo& weaponInfo) {

			//武器モデルを生成。
			CreateModel(weaponInfo.modelFilePath.c_str());

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

		CWeapon* CWeaponBuilder::CreateWeapon(const std::string& weaponName) {

			//武器の雛形を生成。
			CWeapon* weapon = new CWeapon;

			//名前から武器データを取得。
			SWeaponInfo weaponInfo = CWeaponList::GetInstance()->GetWeaponData(weaponName);

			//武器を生成。
			weapon->Create(weaponInfo);

			//生成された武器を返す。
			return weapon;
		}
	}
}
