#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//ˆÚ“®
			//[0].ˆÚ“®‘¬“x
			//[1].¬Œ÷‹——£i‚ ‚ê‚Îj
			class CAITaskMove : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}

