#pragma once
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			//AI�̃V�[�P���X�N���X
			//�^�X�N�����s���Ă����Afalse�ɂȂ�^�X�N������ΏI���B
			class CAISequence : public CAIPart
			{
			public:
				bool Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo)override final;
			};
		}
	}
}