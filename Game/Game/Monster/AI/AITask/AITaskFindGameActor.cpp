#include "YonemaEnginePreCompile.h"
#include "../Utils/StringManipulation.h"
#include "AITaskFindGameActor.h"
#include "../../../GameActor.h"
#include "../../../Player/Player.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskFindGameActor::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//ゲームアクターを検索。
				if (blackboard.m_gameActor == nullptr) {

					//アクターの名前を取得。
					std::string actorName = partInfo[0];

					if (actorName == "Player") {

						blackboard.m_gameActor = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
					}
				}

				//ゲームアクターが見つからなかったら。
				if (blackboard.m_gameActor == nullptr) {

					//アクターの名前を取得。
					std::string actorName = partInfo[0];
#ifdef _DEBUG
					//見つからなかった。
					std::string errorMsg = "指定のアクターが見つかりませんでした。 : ";
					errorMsg += actorName;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif // _DEBUG

					//失敗。
					return false;
				}

				//成功。
				return true;
			}
		}
	}
}