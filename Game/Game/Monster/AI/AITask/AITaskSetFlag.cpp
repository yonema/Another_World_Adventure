#include "YonemaEnginePreCompile.h"
#include "AITaskSetFlag.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskSetFlag::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�t���O�����擾�B
				std::string falgName = partInfo[0];

				//�t���O���擾�B
				bool falg = partInfo[1] == "TRUE" ? true : false;

				//�t���O��ݒ�B
				if (falgName == "IsFindingTarget") {

					blackboard.m_isfindingTarget = falg;
				}
				else {
#ifdef _DEBUG
					//������Ȃ������B
					std::string errorMsg = "CAITaskSetFlag : �w��̃t���O��������܂���ł����B : ";
					errorMsg += falgName;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

					//���s�B
					return false;
#endif // _DEBUG
				}

				//�����B
				return true;
			}
		}
	}
}