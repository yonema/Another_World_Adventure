#pragma once
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//AIのセレクタークラス
			//タスクを実行していき、trueになるタスクがあれば終了。
			class CAISelector : public CAIPart
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}