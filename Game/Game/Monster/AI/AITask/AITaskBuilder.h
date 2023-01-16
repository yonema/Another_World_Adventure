#pragma once
#include "../Utils/StringManipulation.h"
#include "AITaskFindGameActor.h"
#include "AITaskMove.h"
#include "AITaskRotateToTargetPosition.h"
#include "AITaskSetTargetPosition.h"
#include "AITaskWait.h"
#include "AITaskAttack.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//�O���錾
			class CMonsterAITask;

			//�^�X�N�\�z�N���X
			class CAITaskBuilder : nsUtils::SNoncopyable {

			public:
				CMonsterAITask* GetAITask(const std::string& taskName) {

					//�^�X�N�̐��`�𐶐��B
					CMonsterAITask* monsterAITask = nullptr;

					//���O����^�X�N���擾�B

					if (taskName == "FindGameActor") {

						monsterAITask = new CAITaskFindGameActor;
					}
					else if (taskName == "Move") {

						monsterAITask = new CAITaskMove;
					}
					else if (taskName == "RotateToTargetPosition") {

						monsterAITask = new CAITaskRotateToTargetPosition;
					}
					else if (taskName == "SetTargetPosition") {

						monsterAITask = new CAITaskSetTargetPosition;
					}
					else if (taskName == "Wait") {

						monsterAITask = new CAITaskWait;
					}
					else if (taskName == "Attack") {

						monsterAITask = new CAITaskAttack;
					}
					else {

						//������Ȃ������B
						std::string errorMsg = "�^�X�N��������܂���ł����B : ";
						errorMsg += taskName;

						//�x���E�B���h�E���o�́B
						nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					}

					//���^�[���B
					return monsterAITask;
				}
			};
		}
	}
}