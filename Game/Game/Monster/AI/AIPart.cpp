#include "YonemaEnginePreCompile.h"
#include "AIPart.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CAIPart::Release() {

				//子ノードのAI部品を順に破棄。
				for (const auto& AIPart : m_AIPartList) {

					AIPart->Release();
				}

				//デコレーターを順に破棄。
				for (const auto& decorator : m_decoratorList) {

					decorator->Release();
				}

				//自身を破棄。
				delete this;
			}
		}
	}
}