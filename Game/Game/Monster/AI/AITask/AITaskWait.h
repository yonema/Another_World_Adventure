#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//待機
			//[0].待機時間
			class CAITaskWait : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};

		}
	}
}

