#include "YonemaEnginePreCompile.h"
#include "AITaskStandBy.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskStandBy::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//ë“ã@Ç∑ÇÈÅB
				m_AIController->SetState(EnMonsterState::enIdle);

				//ê¨å˜ÅB
				return true;
			}
		}
	}
}