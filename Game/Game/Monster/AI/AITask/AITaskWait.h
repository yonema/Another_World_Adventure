#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//‘Ò‹@
			//[0].‘Ò‹@ŽžŠÔ
			class CAITaskWait : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};

		}
	}
}

