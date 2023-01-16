#include "YonemaEnginePreCompile.h"
#include "../Utils/StringManipulation.h"
#include "AITaskAttack.h"
#include "../../Monster.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			bool CAITaskAttack::Execute(SMonsterAIBlackboard& blackboard, const std::vector<std::string>& partInfo) {

				std::string attackCommandStr = partInfo[0];
				EnMonsterState state = EnMonsterState::enNone;

				if (attackCommandStr == "Weak") {

					//弱攻撃。
					state = EnMonsterState::enWeakAttack;
				}
				else if (attackCommandStr == "Strong") {

					//強攻撃。
					state = EnMonsterState::enStrongAttack;
				}
				else {

#ifdef _DEBUG
					//見つからなかった。
					std::string errorMsg = "指定の攻撃コマンドが見つかりませんでした。 : ";
					errorMsg += attackCommandStr;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif // _DEBUG
					//ステートを設定。
					m_AIController->SetState(state);
				}

				//成功。
				return true;
			}
		}
	}
}