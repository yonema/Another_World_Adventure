#include "YonemaEnginePreCompile.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount = 20.0f;		//�ړ���
			constexpr const float kRotateSpeed = 8.0f;		//��]���x
			constexpr const float kRotationSlerpRate = 9.375f;		//��]�̕�ԗ�
		}

		void CPlayerAction::Init() {

			//�J�����������B
			m_mainCamera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);
		}

		void CPlayerAction::Update(float deltaTime) {

			//deltaTime���X�V(�e�֐��ŕK�v�ɂȂ邽��)�B
			UpdateDeltaTime(deltaTime);

			//�O�������X�V�B
			UpdateForwardDirection();
		}

		void CPlayerAction::Move(float inputX, float inputZ) {

			//�ړ��ʂ��v�Z�B
			CVector3 m_moveAmount = CalculateMoveAmount(inputX, inputZ);

			//�ړ��������v�Z�B
			m_moveDirection = m_moveAmount;
			//���K���B
			m_moveDirection.Normalize();

			//�ړ��B
			m_position += m_moveAmount;
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

		const CVector3& CPlayerAction::CalculateMoveAmount(float inputX, float inputZ) {

			//�J�����̑O�����A�E�������擾�B
			auto cameraForward = m_mainCamera->GetForwardDirection();
			auto cameraRight = m_mainCamera->GetRightDirection();

			//�s�v�Ȑ��������������Đ��K���B
			cameraForward.y = 0.0f;
			cameraForward.Normalize();
			cameraRight.y = 0.0f;
			cameraRight.Normalize();

			//�ړ��ʂ��v�Z�B
			CVector3 moveAmount = CVector3::Zero();
			moveAmount += cameraForward * inputZ * kMoveAmount * m_deltaTimeRef;
			moveAmount += cameraRight * inputX * kMoveAmount * m_deltaTimeRef;

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
	}
}
