#include "YonemaEnginePreCompile.h"
#include "Weapon.h"

namespace nsAWA {

	namespace nsWeapon {

		void CWeapon::Create(const SWeaponInfo& weaponInfo, const char* modelFilePath) {

			//���탂�f���𐶐��B
			CreateModel(modelFilePath);

			//�������ݒ�B
			m_sInfo = weaponInfo;
		}

		void CWeapon::Release() {

			//���탂�f����j���B
			DeleteGO(m_modelRenderer);

			//���g��j���B
			delete this;
		}

		void CWeapon::CreateModel(const char* modelFilePath) {

			//���탂�f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//���탂�f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = modelFilePath;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//���탂�f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(0.1f);
		}

		CWeapon* CWeaponBuilder::Create(const SWeaponInfo& weaponInfo, const char* modelFilePath) {

			//����𐶐��B
			CWeapon* weapon = new CWeapon;
			weapon->Create(weaponInfo, modelFilePath);

			//�������ꂽ�����Ԃ��B
			return weapon;
		}
	}
}
