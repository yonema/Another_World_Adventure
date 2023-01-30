#include "YonemaEnginePreCompile.h"
#include "AITaskFindTarget.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskFindTarget::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//����p���擾�B
				float fieldOfView = std::stof(partInfo[0]);

				//�L���������擾�B
				float distance = std::stof(partInfo[1]);

				//�^�[�Q�b�g�Ɍ������x�N�g�������߂�B
				CVector3 vecToTargetPosition = blackboard.m_targetPosition - m_AIController->GetPosition();

				//�^�[�Q�b�g�Ƃ̋������ݒ��蒷��������B
				if (vecToTargetPosition.Length() > distance) {

					//�������Ȃ��̂Ŏ��s�B
					return false;
				}

				//���K���B
				vecToTargetPosition.Normalize();

				//���g�̑O�������擾�B
				CVector3 forwardDirection = m_AIController->GetForwardDirection();

				//���K���B
				forwardDirection.Normalize();

				//���ς���^�[�Q�b�g�Ƃ̊p�x���v�Z�B
				float resultFieldOfView = nsMath::RadToDeg(std::acos(nsMath::Dot(vecToTargetPosition, forwardDirection)));

				//����ɓ����Ă��邩�v�Z�B
				if (resultFieldOfView <= fieldOfView) {

					//�������̂Ő����B
					return true;
				}

				//���s�B
				return false;
			}
		}
	}
}