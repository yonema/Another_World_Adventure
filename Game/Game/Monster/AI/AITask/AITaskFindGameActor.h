#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//�Q�[���A�N�^�[��T��
			//[0].�A�N�^�[��
			class CAITaskFindGameActor : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}