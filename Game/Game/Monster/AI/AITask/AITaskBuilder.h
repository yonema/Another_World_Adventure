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

			//前方宣言
			class CMonsterAITask;

			//タスク構築クラス
			class CAITaskBuilder : nsUtils::SNoncopyable {

			public:
				CMonsterAITask* GetAITask(const std::string& taskName) {

					//タスクの雛形を生成。
					CMonsterAITask* monsterAITask = nullptr;

					//名前からタスクを取得。

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

						//見つからなかった。
						std::string errorMsg = "タスクが見つかりませんでした。 : ";
						errorMsg += taskName;

						//警告ウィンドウを出力。
						nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
					}

					//リターン。
					return monsterAITask;
				}
			};
		}
	}
}