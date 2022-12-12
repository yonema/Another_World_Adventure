#include "YonemaEnginePreCompile.h"
#include "PlayerWeaponManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const char* const kPlayerWeaponBaseBoneID = "J_Bip_R_Hand";	//�v���C���[�̕��펝���ꏊ
		}

		void CPlayerWeaponManager::Init(const CModelRenderer* playerModel) {

			//�v���C���[���f�����擾�B
			m_playerModel = playerModel;

			//���f���������Ă��Ȃ��Ȃ�B
			if (m_playerModel == nullptr) {

				//�G���[�o�́B
				nsGameWindow::MessageBoxError(L"CPlayerWeaponManager : ���f���̎擾�Ɏ��s���܂����B");
				return;
			}

			//�������������{�[����ID���擾�B
			m_weaponBaseBoneID = m_playerModel->FindBoneId(kPlayerWeaponBaseBoneID);

			//UINT�̍ő�l���Ԃ��Ă�����B
			if (m_weaponBaseBoneID == UINT_MAX) {

				//�{�[����ID�������Ă��Ȃ��̂ŁA�G���[�o�́B
				nsGameWindow::MessageBoxError(L"CPlayerWeaponManager : �{�[���̎擾�Ɏ��s���܂����B");
				return;
			}
		}

		void CPlayerWeaponManager::Update() {

			//�����񂪓����Ă��Ȃ��Ȃ�B
			if (m_weapon == nullptr) {

				//�������^�[���B
				return;
			}

			//�{�[���s����擾�B
			const auto& mBone = m_playerModel->GetBoneMatixWS(m_weaponBaseBoneID);

			// �s�񂩂���W�A��]�A�g�嗦���v�Z���Ċi�[�B
			nsMath::CVector3 bonePos;
			nsMath::CQuaternion boneRot;
			nsMath::CVector3 boneScale;
			nsMath::CalcTRSFromMatrix(bonePos, boneRot, boneScale, mBone);

			//�����transform��ݒ�B
			m_weapon->SetPosition(bonePos);
			m_weapon->SetRotation(boneRot);
			m_weapon->SetScale(boneScale);
		}

		void CPlayerWeaponManager::ChangeWeapon(const nsWeapon::SWeaponInfo& weaponInfo) {

			//���ɕ����񂪓����Ă�����B
			if (m_weapon != nullptr) {

				//�����j���B
				m_weapon->Release();
				m_weapon = nullptr;
			}

#ifdef _DEBUG
			//���Ƀ��f���̃t�@�C���p�X�͎����Œ�`�B
			const char* weaponModelFilePath = "Assets/Models/Sword.fbx";

			//����\�z�N���X�𐶐��B
			nsWeapon::CWeaponBuilder weaponBuilder;

			//����������ɕ���𐶐��B
			m_weapon = weaponBuilder.Create(weaponInfo, weaponModelFilePath);
#endif
		}
	}
}