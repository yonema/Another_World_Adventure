#include "YonemaEnginePreCompile.h"
#include "PlayerAnimationEvent.h"
#include "../../GameActor.h"
#include "../PlayerInput.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			void CPlayerAnimationEvent::CoolTimeOn() {

				//�N�[���^�C����ON�ɂ���B
				m_playerInput->CoolTimeOn();
			}

			void CPlayerAnimationEvent::CoolTimeOff() {

				//�N�[���^�C����OFF�ɂ���B
				m_playerInput->CoolTimeOff();
			}
		}
	}
}