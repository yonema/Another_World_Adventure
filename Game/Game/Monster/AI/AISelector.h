#pragma once
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//AI�̃Z���N�^�[�N���X
			//�^�X�N�����s���Ă����Atrue�ɂȂ�^�X�N������ΏI���B
			class CAISelector : public CAIPart
			{
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}