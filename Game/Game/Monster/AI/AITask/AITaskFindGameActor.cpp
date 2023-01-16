#include "YonemaEnginePreCompile.h"
#include "../Utils/StringManipulation.h"
#include "AITaskFindGameActor.h"
#include "../../../GameActor.h"
#include "../../../Player/Player.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskFindGameActor::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�Q�[���A�N�^�[�������B
				if (blackboard.m_gameActor == nullptr) {

					//�A�N�^�[�̖��O���擾�B
					std::string actorName = partInfo[0];

					if (actorName == "Player") {

						blackboard.m_gameActor = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
					}
				}

				//�Q�[���A�N�^�[��������Ȃ�������B
				if (blackboard.m_gameActor == nullptr) {

					//�A�N�^�[�̖��O���擾�B
					std::string actorName = partInfo[0];
#ifdef _DEBUG
					//������Ȃ������B
					std::string errorMsg = "�w��̃A�N�^�[��������܂���ł����B : ";
					errorMsg += actorName;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif // _DEBUG

					//���s�B
					return false;
				}

				//�����B
				return true;
			}
		}
	}
}