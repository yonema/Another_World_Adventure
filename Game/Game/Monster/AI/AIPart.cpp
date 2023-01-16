#include "YonemaEnginePreCompile.h"
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CAIPart::Release() {

				//qm[hÌAIiðÉjüB
				for (const auto& AIPart : m_AIPartList) {

					AIPart->Release();
				}

				//©gðjüB
				delete this;
			}
		}
	}
}