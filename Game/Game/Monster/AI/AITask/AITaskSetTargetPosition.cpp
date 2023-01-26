#include "YonemaEnginePreCompile.h"
#include "AITaskSetTargetPosition.h"
#include "../Utils/StringManipulation.h"
#include "../../../GameActor.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskSetTargetPosition::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�ڕW�̖��O���擾�B
				std::string moveTargetName = partInfo[0];

				if (moveTargetName == "TargetActor") {

					//�A�N�^�[�B
					blackboard.m_targetPosition = blackboard.m_targetActor->GetPosition();
				}
				else if (moveTargetName == "Forward") {

					//�O�����B
					blackboard.m_targetPosition = m_AIController->GetForwardDirection();
				}
				else if (moveTargetName == "Backward") {

					//�������B
					blackboard.m_targetPosition = m_AIController->GetForwardDirection() * -1.0f;
				}
				else if (moveTargetName == "Random") {

					//�����_���B
					float randomVecX = Random()->GetRangeFloat(-1.0f, 1.0f);
					float randomVecZ = Random()->GetRangeFloat(-1.0f, 1.0f);

					blackboard.m_targetPosition = { randomVecX , 0.0f,randomVecZ };
				}
				else {
#ifdef _DEBUG
					//������Ȃ������B
					std::string errorMsg = "�w��̃^�[�Q�b�g��������܂���ł����B : ";
					errorMsg += moveTargetName;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif
					//���s�B
					return false;
				}

				//�����B
				return true;
			}
		}
	}
}