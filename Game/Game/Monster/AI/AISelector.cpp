#include "YonemaEnginePreCompile.h"
#include "AISelector.h"
#include "AITask/MonsterAITask.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAISelector::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

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