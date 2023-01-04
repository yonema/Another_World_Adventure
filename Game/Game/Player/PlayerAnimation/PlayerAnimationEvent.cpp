#include "YonemaEnginePreCompile.h"
#include "PlayerAnimationEvent.h"
#include "../../GameActor.h"
#include "../PlayerInput.h"
#include "../PlayerAction.h"
#include "../Utils/StringManipulation.h"
#include "../../CreateTrigger.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			void CPlayerAnimationEvent::CoolTimeOn() {

				//クールタイムをONにする。
				m_playerInput->CoolTimeOn();
			}

			void CPlayerAnimationEvent::CoolTimeOff() {

				//クールタイムをOFFにする。
				m_playerInput->CoolTimeOff();

				//ステートを初期化する。
				m_playerInput->ChangeState();
			}

			void CPlayerAnimationEvent::CreateTrigger(const AnimationEventDataStr& animEventDataStr) {

				auto trigger = NewGO<CCreateTrigger>();
				trigger->Create(
					animEventDataStr,
					m_playerAction->GetPosition(),
					m_playerAction->GetForwardDirection()
				);
			}

			void CPlayerAnimationEvent::GetAnimationEvent(const std::string& animationEventName,
			const AnimationEventDataStr& animationEventData
			) {

				//イベントの名前から対応するメンバ関数を呼び出す。

				if (animationEventName == "CoolTimeOn") {

					CoolTimeOn();
				}
				else if (animationEventName == "CoolTimeOff") {

					CoolTimeOff();
				}
				else if (animationEventName == "CreateTrigger") {

					CreateTrigger(animationEventData);
				}
				else {

					std::string errorMsg = "アニメーションイベントが正しく呼ばれていません。 : ";
					errorMsg += animationEventName;

					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
				}
			}
		}
	}
}