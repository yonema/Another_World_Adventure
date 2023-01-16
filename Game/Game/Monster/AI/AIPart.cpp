#include "YonemaEnginePreCompile.h"
#include "AIPart.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			void CAIPart::Release() {

				//子ノードのAI部品を順に破棄。
				for (const auto& AIPart : m_AIPartList) {

					AIPart->Release();
				}

				//自身を破棄。
				delete this;
			}
		}
	}
}