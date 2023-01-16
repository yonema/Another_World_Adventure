#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//–Ú•W‚ÉŒü‚©‚Á‚Ä‰ñ“]‚·‚é
			class CAITaskRotateToTargetPosition : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}

