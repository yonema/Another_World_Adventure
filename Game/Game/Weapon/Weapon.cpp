#include "YonemaEnginePreCompile.h"
#include "Weapon.h"
#include "WeaponList.h"

namespace nsAWA {

	namespace nsWeapon {

		void CWeapon::Create(const SWeaponInfo& weaponInfo) {

			//���탂�f���𐶐��B
			CreateModel(weaponInfo.modelFilePath.c_str());

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

		CWeapon* CWeaponBuilder::CreateWeapon(const std::string& weaponName) {

			//����̐��`�𐶐��B
			CWeapon* weapon = new CWeapon;

			//���O���畐��f�[�^���擾�B
			SWeaponInfo weaponInfo = CWeaponList::GetInstance()->GetWeaponData(weaponName);

			//����𐶐��B
			weapon->Create(weaponInfo);

			//�������ꂽ�����Ԃ��B
			return weapon;
		}
	}
}
