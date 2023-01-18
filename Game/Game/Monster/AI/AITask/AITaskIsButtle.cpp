#include "YonemaEnginePreCompile.h"
#include "AITaskIsButtle.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr float kDistanceforButtle = 80.0f;		//バトルを続けるための距離
			}

			bool CAITaskIsButtle::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//ターゲットとの距離を計算。
				CVector3 distanceToTarget = blackboard.m_targetPosition - m_AIController->GetPosition();

				//一定距離以内なら。
				if (distanceToTarget.Length() <= kDistanceforButtle) {

					//成功。
					return true;
				}
				else {

					//失敗。
					return false;
				}
			}
		}
	}
}