#include "YonemaEnginePreCompile.h"
#include "PlayerAnimationEvent.h"
#include "../../GameActor.h"
#include "../PlayerInput.h"

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
			}
		}
	}
}