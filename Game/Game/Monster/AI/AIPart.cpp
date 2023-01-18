#include "YonemaEnginePreCompile.h"
#include "AIPart.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CAIPart::Release() {

				//�q�m�[�h��AI���i�����ɔj���B
				for (const auto& AIPart : m_AIPartList) {

					AIPart->Release();
				}

				//�f�R���[�^�[�����ɔj���B
				for (const auto& decorator : m_decoratorList) {

					decorator->Release();
				}

				//���g��j���B
				delete this;
			}
		}
	}
}