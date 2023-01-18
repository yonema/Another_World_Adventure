#include "YonemaEnginePreCompile.h"
#include "AIDecorator.h"
#include "MonsterAIBlackboard.h"

namespace nsAWA {

	namespace nsMonster {

		namespace nsMonsterAI {

			namespace {

				constexpr char kDelimiter = '!';	//区切り文字
			}

			void CAIDecorator::Init(bool* flag) {

				//フラグを取得。
				m_falgRef = flag;
			}

			void CAIDecorator::Release() {

				delete this;
			}

			CAIDecorator* CAIDecoratorBuilder::CreateDecorator(const std::string& flagStr, SMonsterAIBlackboard* blackboard) {

				//デコレーターを生成。
				CAIDecorator* decorator = new CAIDecorator;

				//文字列を取得。
				std::string flagStrLocal = flagStr;

				//先頭文字が区切り文字になっていたら。
				if (flagStrLocal[0] == kDelimiter) {

					//逆の評価をするよう設定。
					decorator->Reverse();
					flagStrLocal.erase(flagStrLocal.begin());
				}

				//フラグを設定。
				if (flagStrLocal == "IsFindingTarget") {

					decorator->Init(&blackboard->m_isfindingTarget);
				}
				else {
#ifdef _DEBUG
					//見つからなかった。
					std::string errorMsg = "CAIDecorator : 指定のフラグが見つかりませんでした。 : ";
					errorMsg += flagStrLocal;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
#endif // _DEBUG
				}

				

				return decorator;
			}
		}
	}
}