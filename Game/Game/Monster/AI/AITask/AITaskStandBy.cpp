#include "YonemaEnginePreCompile.h"
#include "AITaskStandBy.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskStandBy::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//待機する。
				m_AIController->SetState(EnMonsterState::enIdle);

				//成功。
				return true;
			}
		}
	}
}