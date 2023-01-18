#include "YonemaEnginePreCompile.h"
#include "AISequence.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAISequence::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//�f�R���[�^�[�����ɎQ�ƁB
				for (const auto& decorator : m_decoratorList) {

					//�t���O��false�Ȃ�AI���i������܂ł��Ȃ�false�ő������^�[���B
					if (!decorator->Evaluate()) {

						return false;
					}
				}

				//AI���i�����ɎQ�ƁB
				for (const auto& AIPart : m_AIPartList) {

					//���s�B
					bool isOk = AIPart->Execute(blackboard, AIPart->GetPartInfo());

					//AI���i��false�ŏI�������Ȃ�B
					if (!isOk) {

						//���̃V�[�P���X��false�ŏI���B
						return false;
					}
				}

				//���ׂĂ�AI���i��true�ŏI�������̂ł��̃V�[�P���X��true�ŏI���B
				return true;
			}
		}
	}
}