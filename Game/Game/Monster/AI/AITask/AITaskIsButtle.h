#pragma once
#include "MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//�o�g�������ǂ������ׂ�i�^�[�Q�b�g����苗���ɂ��邩�j
			class CAITaskIsButtle : public CMonsterAITask
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}

