#pragma once
#include "../AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//�^�X�N
			class CMonsterAITask : public CAIPart
			{
			public:
				virtual bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) = 0;

			};
		}
	}
}