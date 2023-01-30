#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//フラグを設定する
			//[0].フラグ名
			//[1].TRUE or FALSE
			class CAITaskSetFlag : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}

