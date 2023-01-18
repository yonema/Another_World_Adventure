#include "YonemaEnginePreCompile.h"
#include "AISelector.h"
#include "AITask/MonsterAITask.h"
#include "AIDecorator.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAISelector::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//デコレーターを順に参照。
				for (const auto& decorator : m_decoratorList) {

					//フラグがfalseならAI部品を見るまでもなくfalseで早期リターン。
					if (!decorator->Evaluate()) {

						return false;
					}

				}
				//AI部品を順に参照。
				for (const auto& AIPart : m_AIPartList) {

					//実行。
					bool isOk = AIPart->Execute(blackboard, AIPart->GetPartInfo());

					//AI部品がtrueで終了したなら。
					if (isOk) {

						//このシーケンスはtrueで終了。
						return true;
					}
				}

				//すべてのAI部品がfalseで終了したのでこのシーケンスはfalseで終了。
				return false;
			}
		}
	}
}