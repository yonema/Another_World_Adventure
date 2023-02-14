#include "YonemaEnginePreCompile.h"
#include "PlayerWeaponManager.h"
#include "PlayerAction.h"
#include "Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const char* const kPlayerWeaponBaseBoneID = "J_Bip_R_Hand";	//�v���C���[�̕��펝���ꏊ
			constexpr float kEffectAddPosition = 10.0f;		//�G�t�F�N�g�����ꏊ
			constexpr float kEffectScale = 2.0f;		//�G�t�F�N�g�T�C�Y
		}

		void CPlayerWeaponManager::Init(const CPlayer* player, const CModelRenderer* playerModel, const CPlayerAction* action) {

			//�v���C���[���i�[�B
			m_player = player;

			//�v���C���[���f�����擾�B
			m_playerModel = playerModel;

			//�v���C���[�A�N�V�������擾�B
			m_playerAction = action;

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

			//�X���ɂ���Ȃ�B
			if (m_player->IsInTown()) {

				//����𖳌����B
				m_weapon->GetModelRenderer()->ModelDeactivate();

				//�I���B
				return;
			}
			else {

				//�����L�����B
				m_weapon->GetModelRenderer()->ModelActivate();
			}

			//�X�L���g�p������Ȃ��A�G�t�F�N�g�������Ă�����B
			if (m_playerAction->GetState() != EnPlayerState::enUseActiveSkill
				&& m_mainEffect != nullptr
				) {

				//�G�t�F�N�g��j���B
				m_mainEffect->Stop();
				DeleteGO(m_mainEffect);
				m_mainEffect = nullptr;
			}

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

			//�G�t�F�N�g�������Ă���Ȃ�B
			if (m_mainEffect != nullptr) {

				//�G�t�F�N�g���X�V�B
				UpdateEffect();
			}
		}

		void CPlayerWeaponManager::ChangeWeapon(nsWeapon::CWeapon* weapon) {

			//���ɕ����񂪓����Ă�����B
			if (m_weapon != nullptr) {

				//�����j���B
				m_weapon->Release();
				m_weapon = nullptr;
			}

			//�����ݒ�B
			m_weapon = weapon;
		}

		void CPlayerWeaponManager::CreateEffect(const std::string& effectFilePath) {

			//���C���G�t�F�N�g�𐶐��B
			m_mainEffect = NewGO<CEffectPlayer>();
			std::string mainEffectFilePath = "Assets/Effects/Weapon/";
			mainEffectFilePath += effectFilePath;
			mainEffectFilePath += ".efkefc";

			//�������B
			m_mainEffect->Init(nsUtils::GetWideStringFromString(mainEffectFilePath).c_str());

			//�X�V�B
			UpdateEffect();

			//�G�t�F�N�g���Đ��B
			m_mainEffect->Play();
		}

		void CPlayerWeaponManager::UpdateEffect() {

			//�G�t�F�N�g�����ꏊ���擾�B
			CVector3 weaponBasePosition = CVector3::Down();

			const CQuaternion& rot = m_weapon->GetModelRenderer()->GetRotation();

			rot.Apply(weaponBasePosition);

			weaponBasePosition *= kEffectAddPosition;

			//�G�t�F�N�g�̍��W�Ɖ�]��ݒ�B
			m_mainEffect->SetPosition(m_weapon->GetPosition() + weaponBasePosition);
			m_mainEffect->SetRotation(m_weapon->GetRotation());
			m_mainEffect->SetScale(kEffectScale);
		}
	}
}