#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//�ڕW�̍��W�����߂�
			//[0].�ڕW�iTargetActor�AForward�ABackward�ARandom�Ȃǁj
			class CAITaskSetTargetPosition : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}

