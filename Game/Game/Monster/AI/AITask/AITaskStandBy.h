#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//���������ҋ@����
			//CAITaskWait�ƈ���ăr�w�C�r�A�c���[�͏펞���s�����
			class CAITaskStandBy : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}

