#include "YonemaEnginePreCompile.h"
#include "AITaskRotateToTargetPosition.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr const float kRotationSlerpRate = 9.375f;			//��]�̕�ԗ�
			}

			bool CAITaskRotateToTargetPosition::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//��]�̐��`�𐶐��B
				CQuaternion rotation = CQuaternion::Identity();

				//�ڕW�Ǝ��g�̍��W����ړ����������߂�B
				CVector3 moveDirection = blackboard.m_targetPosition - m_AIController->GetPosition();

				//���K���B
				moveDirection.Normalize();

				//��]�p�x�����߂�B
				float angle = atan2(-moveDirection.x, moveDirection.z);

				//��]����ݒ�B
				CQuaternion rotSource = CQuaternion::Identity();
				rotSource.SetRotation(CVector3::AxisY(), -angle);

				//��Ԃ��邩�ǂ������擾�B
				bool slerp = partInfo[0] == "TRUE" ? true : false;

				//��Ԃ��邩�ǂ����B
				if (slerp) {

					//��]�����擾�B
					rotation = m_AIController->GetRotation();

					//��]���x�̕�ԗ������߂�B
					float rotationSlerpRate = kRotationSlerpRate * m_AIController->GetDeltaTimeRef();

					//���`��ԁB
					rotation.Slerp(rotationSlerpRate, rotation, rotSource);
				}
				else {

					//���̂܂ܐݒ�B
					rotation = rotSource;
				}

				//��]��ݒ�B
				m_AIController->SetRotation(rotation);

				//�O�������X�V�B
				m_AIController->UpdateForwardDirection();

				//�����B
				return true;
			}
		}
	}
}