#include "YonemaEnginePreCompile.h"
#include "../Utils/StringManipulation.h"
#include "AITaskAttack.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskAttack::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				std::string attackCommandStr = partInfo[0];
				EnMonsterState state = EnMonsterState::enNone;

				if (attackCommandStr == "Weak") {

					//��U���B
					state = EnMonsterState::enWeakAttack;
				}
				else if (attackCommandStr == "Strong") {

					//���U���B
					state = EnMonsterState::enStrongAttack;
				}
				else {

#ifdef _DEBUG
					//������Ȃ������B
					std::string errorMsg = "�w��̍U���R�}���h��������܂���ł����B : ";
					errorMsg += attackCommandStr;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif // _DEBUG
					//�X�e�[�g��ݒ�B
					m_AIController->SetState(state);
				}

				//�����B
				return true;
			}
		}
	}
}