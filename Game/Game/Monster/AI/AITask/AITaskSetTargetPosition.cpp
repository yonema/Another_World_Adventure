#include "YonemaEnginePreCompile.h"
#include "AITaskSetTargetPosition.h"
#include "../Utils/StringManipulation.h"
#include "../../../GameActor.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskSetTargetPosition::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//目標の名前を取得。
				std::string moveTargetName = partInfo[0];

				if (moveTargetName == "TargetActor") {

					//アクター。
					blackboard.m_targetPosition = blackboard.m_targetActor->GetPosition();
				}
				else if (moveTargetName == "Forward") {

					//前方向。
					blackboard.m_targetPosition = m_AIController->GetForwardDirection();
				}
				else if (moveTargetName == "Backward") {

					//後ろ方向。
					blackboard.m_targetPosition = m_AIController->GetForwardDirection() * -1.0f;
				}
				else if (moveTargetName == "Random") {

					//ランダム。
					float randomVecX = Random()->GetRangeFloat(-1.0f, 1.0f);
					float randomVecZ = Random()->GetRangeFloat(-1.0f, 1.0f);

					blackboard.m_targetPosition = { randomVecX , 0.0f,randomVecZ };
				}
				else {
#ifdef _DEBUG
					//見つからなかった。
					std::string errorMsg = "指定のターゲットが見つかりませんでした。 : ";
					errorMsg += moveTargetName;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif
					//失敗。
					return false;
				}

				//成功。
				return true;
			}
		}
	}
}