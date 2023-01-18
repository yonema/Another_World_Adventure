#include "YonemaEnginePreCompile.h"
#include "AITaskSetFlag.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskSetFlag::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				//フラグ名を取得。
				std::string falgName = partInfo[0];

				//フラグを取得。
				bool falg = partInfo[1] == "TRUE" ? true : false;

				//フラグを設定。
				if (falgName == "IsFindingTarget") {

					blackboard.m_isfindingTarget = falg;
				}
				else {
#ifdef _DEBUG
					//見つからなかった。
					std::string errorMsg = "CAITaskSetFlag : 指定のフラグが見つかりませんでした。 : ";
					errorMsg += falgName;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

					//失敗。
					return false;
#endif // _DEBUG
				}

				//成功。
				return true;
			}
		}
	}
}