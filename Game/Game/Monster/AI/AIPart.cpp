#include "YonemaEnginePreCompile.h"
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CAIPart::Release() {

				//�q�m�[�h��AI���i�����ɔj���B
				for (const auto& AIPart : m_AIPartList) {

					AIPart->Release();
				}

				//���g��j���B
				delete this;
			}
		}
	}
}