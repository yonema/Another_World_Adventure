#include "YonemaEnginePreCompile.h"
#include "AITaskStandBy.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskStandBy::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�ҋ@����B
				m_AIController->SetState(EnMonsterState::enIdle);

				//�����B
				return true;
			}
		}
	}
}