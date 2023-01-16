#include "YonemaEnginePreCompile.h"
#include "AITaskWait.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskWait::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				if (m_AIController->GetState() == EnMonsterState::enIdle) {

					//タイマーを更新。
					blackboard.m_waitTimer -= m_AIController->GetDeltaTimeRef();

					//タイマーが0になったら。
					if (blackboard.m_waitTimer <= 0.0f) {

						//待機が終わったので成功。
						return true;
					}
					else {

						//まだ待機中。
						return false;
					}
				}
				else {

					//AIコントローラーにこの待機タスクを設定。
					m_AIController->SetWaitNode(this);

					//ステートを待機状態に設定。
					m_AIController->SetState(EnMonsterState::enIdle);

					//待機時間を取得。
					float waitTime = std::stof(partInfo[0]);

					//待機時間を設定。
					blackboard.m_waitTimer = waitTime;

					//待機していて、これ以上進めたくないので失敗とする。
					return false;
				}
			}
		}
	}
}