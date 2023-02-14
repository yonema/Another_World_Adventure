#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"
#include "../Skill/ActiveSkill.h"
#include "PlayerManager.h"
#include "../Feature/FeatureManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount_Walk = 40.0f;				//������Ԃ̈ړ���
			constexpr const float kMoveAmount_Dash = 1.3f;				//�_�b�V����Ԃ̈ړ��{��
			constexpr const float kRotationSlerpRate = 9.375f;			//��]�̕�ԗ�
			constexpr const float kAutoHealMPValue = 10.0f;				//MP�����񕜗ʁi��/s�j
			constexpr const float kAutoHealSPValue = 10.0f;				//SP�����񕜗ʁi��/s�j
			constexpr const float kAutoHealGuardGaugeValue = 20.0f;		//�K�[�h�Q�[�W�̒l�����񕜗ʁi��/s�j
			constexpr const float kDashSPDamage = 10.0f;				//�_�b�V���ɂ��SP�����ʁi��/s�j
			constexpr const float kGuardGauge100 = 100.0f;				//�K�[�h�Q�[�W�̍ő�l�i100�ƒ�`����j
			constexpr const float kPerMax = 100.0f;						//�ő偓
		}

		void CPlayerAction::Init(
			CVector3& position,
			CQuaternion& rotation,
			CPlayerStatus* playerStatus, 
			nsFeature::CFeatureManager* playerFeatureManager,
			nsPlayerAnimation::CPlayerAnimation* playerAnimation
		) {
			//���W���擾�B
			m_position = &position;

			//��]���擾�B
			m_rotation = &rotation;

			//�J�����������B
			m_mainCamera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

			//�v���C���[�̃X�e�[�^�X��ێ��B
			m_playerStatus = playerStatus;

			//�v���C���[�̃X�e�[�^�X�ω��Ǘ��N���X��ێ��B
			m_playerFeatureManager = playerFeatureManager;

			//�v���C���[�A�j���[�V�����̃|�C���^���擾�B
			m_playerAnimation = playerAnimation;
		}

		void CPlayerAction::Release() {

			//�A�N�e�B�u�X�L����j���B
			for (auto& activeSkill : m_activeSkill) {

				if (activeSkill != nullptr) {

					delete activeSkill;
					activeSkill = nullptr;
				}
			}
		}

		void CPlayerAction::Update(float deltaTime) {

			//deltaTime���X�V(�e�֐��ŕK�v�ɂȂ邽��)�B
			UpdateDeltaTime(deltaTime);

			//MP�������񕜁B
			AutoHealMP();

			//SP�������񕜁B
			AutoHealSP();

			//�K�[�h���ȊO���B
			if (m_state != EnPlayerState::enGuard) {
				
				//�K�[�h�Q�[�W�̒l�������񕜁B
				AutoHealGuardGaugeValue();
			}

			//�X�^�������K�[�h�Q�[�W��100�ɂȂ�����i�ő�l���Ƃ�Ȃ��̂̓o�t�f�o�t�ōő�l���ω�����\�������邽�߁j
			if (m_state == EnPlayerState::enStun
				&& fabsf(m_playerStatus->GetGuardGaugeValue() - kGuardGauge100) < FLT_EPSILON
				) {

				//�X�^�����������A�ҋ@��Ԃɂ���B
				SetState(EnPlayerState::enIdle);
			}
		}

		void CPlayerAction::Move(float inputX, float inputZ, float speed) {

			//�_�b�V����Ԃ��B
			if (m_state == EnPlayerState::enRun) {

				//�_�b�V���ɂ��ASP������������B
				DamageSPDash();
			}

			//�ړ��ʂ��v�Z�B
			CVector3 moveAmount = CalculateMoveAmount(inputX, inputZ, speed);

			//�ړ��������v�Z�B
			m_moveDirection = moveAmount;
			//���K���B
			m_moveDirection.Normalize();

			//�ړ��B
			*m_position += moveAmount;
		}

		void CPlayerAction::Rotate(bool slerp) {

			//���͂ɂ���]�p�x�����߂�B
			float angle = atan2(-m_moveDirection.x, m_moveDirection.z);

			//��]����ݒ�B
			CQuaternion rotSource = CQuaternion::Identity();
			rotSource.SetRotation(CVector3::AxisY(), -angle);

			//��Ԃ���H
			if (slerp) {
				//��]���x�̕�ԗ������߂�B
				float rotationSlerpRate = kRotationSlerpRate * m_deltaTimeRef;

				//���`��ԁB
				(*m_rotation).Slerp(rotationSlerpRate, *m_rotation, rotSource);
			}
			else {

				//���̂܂ܐݒ�B
				*m_rotation = rotSource;
			}
		}

		void CPlayerAction::Guard() {

			//�K�[�h��Ԃɐݒ�B
			m_state = EnPlayerState::enGuard;
		}

		void CPlayerAction::UseItem() {

			//�A�C�e���Ǘ��N���X���擾�B
			auto itemManager = CPlayerManager::GetInstance()->GetItemManager();

			//�A�C�e���������Ă�����B
			if (itemManager->HasItem()) {
			
				//�I�𒆂̃A�C�e�����g�p�B
				itemManager->UseItem();
			
				//�A�C�e���g�p��Ԃɂ���B
				SetState(EnPlayerState::enUseItem);
			}
		}

		void CPlayerAction::SetActiveSkill(int activeSkillNum, nsSkill::CActiveSkill* activeSkill) {

			//���ݓo�^���Ă���A�N�e�B�u�X�L����j���B
			if (m_activeSkill[activeSkillNum] != nullptr) {

				delete m_activeSkill[activeSkillNum];
				m_activeSkill[activeSkillNum] = nullptr;
			}

			//�V���ɃA�N�e�B�u�X�L����ݒ�B
			m_activeSkill[activeSkillNum] = activeSkill;
		}

		nsSkill::CActiveSkill* CPlayerAction::GetActiveSkill(int activeSkillNum)const {

			//�͈͊O�̔ԍ��w������Ă�����B
			if (activeSkillNum > nsSkill::CActiveSkill::m_kActiveSkillNumMax) {

				//�G���[�o�́B
				nsGameWindow::MessageBoxError(L"�͈͊O�̃A�N�e�B�u�X�L���ԍ��ł��B");
				std::abort();
			}

			//�A�N�e�B�u�X�L�����擾�B
			return m_activeSkill[activeSkillNum];
		}

		void CPlayerAction::UseActiveSkill(EnActiveSkillListNumber activeSkillNum) {

			//����MP���擾�B
			float useMP = m_activeSkill[static_cast<int>(activeSkillNum)]->GetUseMP();

			//MP������Ȃ��Ȃ�B
			if (m_playerStatus->GetMP() < useMP) {

				//�������^�[���B
				return;
			}

			//MP������B
			m_playerStatus->DamageMP(useMP);

			//�X�L�������s�B
			m_activeSkill[static_cast<int>(activeSkillNum)]->Execute();

			//�A�N�e�B�u�X�L�����g�p�ł��Ȃ���Ԃ�������B
			if (!m_playerFeatureManager->CanUseActiveSkill()) {

				//��p�G�t�F�N�g���Đ��B�i�������j

				//�I���B
				return;
			}

			//�A�N�e�B�u�X�L���̃A�j���[�V������\��B
			m_playerAnimation->ReserveActiveSkillAnimation(m_activeSkill[static_cast<int>(activeSkillNum)]);

			//�A�N�e�B�u�X�L���g�p��ԂɁB
			SetState(EnPlayerState::enUseActiveSkill);
		}

		const CVector3 CPlayerAction::CalculateMoveAmount(float inputX, float inputZ, float speed) {

			//�J�����̑O�����A�E�������擾�B
			auto cameraForward = m_mainCamera->GetForwardDirection();
			auto cameraRight = m_mainCamera->GetRightDirection();

			//�s�v�Ȑ��������������Đ��K���B
			cameraForward.y = 0.0f;
			cameraForward.Normalize();
			cameraRight.y = 0.0f;
			cameraRight.Normalize();

			//�ړ����x���������B
			float moveAmountf = 0.0f;

			//�_�b�V����Ԃ��B
			if (m_state == EnPlayerState::enRun) {

				//���鑬�x�����B
				moveAmountf = kMoveAmount_Walk * kMoveAmount_Dash;
			}
			else if (speed > FLT_EPSILON) {

				moveAmountf = speed;
			}
			else {
				//�������x�����B
				moveAmountf = kMoveAmount_Walk;
			}

			//�ړ��ʂ��v�Z�B
			CVector3 moveAmount = CVector3::Zero();
			moveAmount += cameraForward * inputZ * moveAmountf * m_deltaTimeRef;
			moveAmount += cameraRight * inputX * moveAmountf * m_deltaTimeRef;

			//���^�[���B
			return moveAmount;
		}

		void CPlayerAction::AutoHealMP() {

			//�񕜗ʂ��v�Z�B
			float healValue = m_playerStatus->GetMaxMP() * (kAutoHealMPValue / kPerMax) * m_deltaTimeRef;

			//MP�������񕜁B
			m_playerStatus->HealMP(healValue);
		}

		void CPlayerAction::AutoHealSP() {

			//�񕜗ʂ��v�Z�B
			float healValue = m_playerStatus->GetMaxSP() * (kAutoHealSPValue / kPerMax) * m_deltaTimeRef;

			//SP�������񕜁B
			m_playerStatus->HealSP(healValue);
		}

		void CPlayerAction::DamageSPDash() {

			//����ʂ��v�Z�B
			float damageValue = m_playerStatus->GetMaxSP() * (kDashSPDamage / kPerMax) * m_deltaTimeRef;

			//SP������B
			m_playerStatus->DamageSP(damageValue);
		}

		void CPlayerAction::AutoHealGuardGaugeValue() {

			//�񕜗ʂ��v�Z�B
			float healValue = m_playerStatus->GetMaxGuardGaugeValue() * (kAutoHealGuardGaugeValue / kPerMax) * m_deltaTimeRef;

			//�K�[�h�Q�[�W�������񕜁B
			m_playerStatus->HealGuardGaugeValue(healValue);
		}
	}
}
