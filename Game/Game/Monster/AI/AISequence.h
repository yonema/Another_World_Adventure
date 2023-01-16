#pragma once
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//AIのシーケンスクラス
			//タスクを実行していき、falseになるタスクがあれば終了。
			class CAISequence : public CAIPart
			{
			public:
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}