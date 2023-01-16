#include "YonemaEnginePreCompile.h"
#include "AISelector.h"
#include "AITask/MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAISelector::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//AI���i�����ɎQ�ƁB
				for (const auto& AIPart : m_AIPartList) {

					//���s�B
					bool isOk = AIPart->Execute(blackboard, AIPart->GetPartInfo());

					//AI���i��true�ŏI�������Ȃ�B
					if (isOk) {

						//���̃V�[�P���X��true�ŏI���B
						return true;
					}
				}

				//���ׂĂ�AI���i��false�ŏI�������̂ł��̃V�[�P���X��false�ŏI���B
				return false;
			}
		}
	}
}