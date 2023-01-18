#include "YonemaEnginePreCompile.h"
#include "AIPart.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CAIPart::Release() {

				//qm[hÌAIiðÉjüB
				for (const auto& AIPart : m_AIPartList) {

					AIPart->Release();
				}

				//fR[^[ðÉjüB
				for (const auto& decorator : m_decoratorList) {

					decorator->Release();
				}

				//©gðjüB
				delete this;
			}
		}
	}
}