#include "YonemaEnginePreCompile.h"
#include "AITaskRotateToTargetPosition.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr const float kRotationSlerpRate = 9.375f;			//��]�̕�ԗ�
			}

			bool CAITaskRotateToTargetPosition::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�ڕW�Ǝ��g�̍��W����ړ����������߂�B
				CVector3 moveDirection = blackboard.m_targetPosition - m_AIController->GetPosition();

				//���K���B
				moveDirection.Normalize();

				//��]�p�x�����߂�B
				float angle = atan2(-moveDirection.x, moveDirection.z);

				//��]����ݒ�B
				CQuaternion rotSource = CQuaternion::Identity();
				rotSource.SetRotation(CVector3::AxisY(), -angle);

				//��]���x�̕�ԗ������߂�B
				float rotationSlerpRate = kRotationSlerpRate * m_AIController->GetDeltaTimeRef();

				//���`��ԁB
				CQuaternion rotation = m_AIController->GetRotation();
				rotation.Slerp(rotationSlerpRate, rotation, rotSource);

				//��]��ݒ�B
				m_AIController->SetRotation(rotation);

				//�����B
				return true;
			}
		}
	}
}