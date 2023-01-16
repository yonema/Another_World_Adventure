#include "YonemaEnginePreCompile.h"
#include "AISequence.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAISequence::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//AI部品を順に参照。
				for (const auto& AIPart : m_AIPartList) {

					//実行。
					bool isOk = AIPart->Execute(blackboard, AIPart->GetPartInfo());

					//AI部品がfalseで終了したなら。
					if (!isOk) {

						//このシーケンスはfalseで終了。
						return false;
					}
				}

				//すべてのAI部品がtrueで終了したのでこのシーケンスはtrueで終了。
				return true;
			}
		}
	}
}