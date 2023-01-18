#include "YonemaEnginePreCompile.h"
#include "AITaskBark.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskBark::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//ステートを設定。
				m_AIController->SetState(EnMonsterState::enBark);

				//クールタイムをONに設定。
				m_AIController->CoolTimeOn();

				//成功。
				return true;
			}
		}
	}
}