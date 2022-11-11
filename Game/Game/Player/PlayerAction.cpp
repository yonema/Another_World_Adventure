#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount_Walk = 20.0f;				//������Ԃ̈ړ���
			constexpr const float kMoveAmount_Dash = 30.0f;				//�_�b�V����Ԃ̈ړ���
			constexpr const float kRotationSlerpRate = 9.375f;			//��]�̕�ԗ�
			constexpr const float kAutoHealMPTimeInterval = 0.1f;		//MP�����񕜊Ԋu
			constexpr const int kAutoHealMPValue = 1;					//MP�����񕜗�
			constexpr const float kAutoHealSPTimeInterval = 0.1f;		//SP�����񕜊Ԋu
			constexpr const int kAutoHealSPValue = 1;					//SP�����񕜗�
			constexpr const float kAutoHealGuardGaugeInterval = 0.1f;	//�K�[�h�Q�[�W�̒l�����񕜊Ԋu
			constexpr const int kAutoHealGuardGaugeValueAmount = 1;		//�K�[�h�Q�[�W�̒l�����񕜗�
			constexpr const int kDashSPDamage = 2;						//�_�b�V���ɂ��SP������
			constexpr const float kDashSPTimeInterval = 0.1f;			//�_�b�V���ɂ��SP�����Ԋu
		}

		void CPlayerAction::Init() {

			//�J�����������B
			m_mainCamera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

			//�v���C���[�������B
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);

			//�v���C���[�̃X�e�[�^�X��ێ��B
			m_playerStatus = player->GetStatus();
		}

		void CPlayerAction::Update(float deltaTime) {

			//deltaTime���X�V(�e�֐��ŕK�v�ɂȂ邽��)�B
			UpdateDeltaTime(deltaTime);

			//�O�������X�V�B
			UpdateForwardDirection();

			//MP�������񕜁B
			AutoHealMP();

			//SP�������񕜁B
			AutoHealSP();

			//�K�[�h���ȊO���B
			if (m_state != EnPlayerState::enGuard) {
				
				//�K�[�h�Q�[�W�̒l�������񕜁B
				AutoHealGuardGaugeValue();
			}
		}

		void CPlayerAction::Move(float inputX, float inputZ) {

			//�_�b�V����Ԃ��B
			if (m_state == EnPlayerState::enDash) {

				//�_�b�V���ɂ��ASP������������B
				DamageSPDash();
			}

			//�ړ��ʂ��v�Z�B
			CVector3 moveAmount = CalculateMoveAmount(inputX, inputZ);

			//�ړ��������v�Z�B
			m_moveDirection = moveAmount;
			//���K���B
			m_moveDirection.Normalize();

			//�ړ��B
			m_position += moveAmount;
		}

		void CPlayerAction::Rotate() {

			//���͂ɂ���]�p�x�����߂�B
			float angle = atan2(-m_moveDirection.x, m_moveDirection.z);

			//��]����ݒ�B
			CQuaternion rotSource = CQuaternion::Identity();
			rotSource.SetRotation(CVector3::AxisY(), -angle);

			//��]���x�̕�ԗ������߂�B
			float rotationSlerpRate = kRotationSlerpRate * m_deltaTimeRef;

			//���`��ԁB
			m_rotation.Slerp(rotationSlerpRate, m_rotation, rotSource);
		}

		void CPlayerAction::Guard() {

			//�K�[�h��Ԃɐݒ�B
			m_state = EnPlayerState::enGuard;
		}

#ifdef _DEBUG
		void CPlayerAction::StrongAttack() {

			//���U�����J��o���B
			//...

			//SP�������B
			m_playerStatus->DamageSP(30);
		}
#endif

		const CVector3& CPlayerAction::CalculateMoveAmount(float inputX, float inputZ) {

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
			if (m_state == EnPlayerState::enDash) {

				//���鑬�x�����B
				moveAmountf = kMoveAmount_Dash;
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

		void CPlayerAction::UpdateForwardDirection() {

			//��]�s����v�Z�B
			auto mRot = CMatrix::Identity();
			mRot.MakeRotationFromQuaternion(m_rotation);

			//�O������ݒ�B
			m_forwardDirection.x = mRot.m_fMat[2][0];
			m_forwardDirection.y = mRot.m_fMat[2][1];
			m_forwardDirection.z = mRot.m_fMat[2][2];

			//���K���B
			m_forwardDirection.Normalize();
		}

		void CPlayerAction::AutoHealMP() {

			//�^�C�}�[�����Z�B
			m_healMPTimer += m_deltaTimeRef;

			//�^�C�}�[�����Ԋu���𒴂�����B
			if (m_healMPTimer >= kAutoHealMPTimeInterval) {

				//MP�������񕜁B
				m_playerStatus->HealMP(kAutoHealMPValue);

				//�^�C�}�[�����Z�B
				m_healMPTimer -= kAutoHealMPTimeInterval;
			}
		}

		void CPlayerAction::AutoHealSP() {

			//�^�C�}�[�����Z�B
			m_healSPTimer += m_deltaTimeRef;

			//�^�C�}�[�����Ԋu���𒴂�����B
			if (m_healSPTimer >= kAutoHealSPTimeInterval) {

				//SP�������񕜁B
				m_playerStatus->HealSP(kAutoHealSPValue);

				//�^�C�}�[�����Z�B
				m_healSPTimer -= kAutoHealSPTimeInterval;
			}
		}

		void CPlayerAction::DamageSPDash() {

			//�^�C�}�[�����Z�B
			m_dashSPTimer += m_deltaTimeRef;

			//�^�C�}�[�����Ԋu���𒴂�����B
			if (m_dashSPTimer >= kDashSPTimeInterval) {

				//SP�������B
				m_playerStatus->DamageSP(kDashSPDamage);

				//�^�C�}�[�����Z�B
				m_dashSPTimer -= kDashSPTimeInterval;
			}
		}

		void CPlayerAction::AutoHealGuardGaugeValue() {

			//�^�C�}�[�����Z�B
			m_healGuardGaugeValueTimer += m_deltaTimeRef;

			//�^�C�}�[�����Ԋu���𒴂�����B
			if (m_healGuardGaugeValueTimer >= kAutoHealGuardGaugeInterval) {

				//�K�[�h�Q�[�W�̒l�������񕜁B
				m_playerStatus->HealGuardGaugeValue(kAutoHealGuardGaugeValueAmount);

				//�^�C�}�[�����Z�B
				m_healGuardGaugeValueTimer -= kAutoHealGuardGaugeInterval;
			}
		}
	}
}
