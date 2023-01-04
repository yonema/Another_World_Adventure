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

				//�N�[���^�C����ON�ɂ���B
				m_playerInput->CoolTimeOn();
			}

			void CPlayerAnimationEvent::CoolTimeOff() {

				//�N�[���^�C����OFF�ɂ���B
				m_playerInput->CoolTimeOff();

				//�X�e�[�g������������B
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

				//�C�x���g�̖��O����Ή����郁���o�֐����Ăяo���B

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

					std::string errorMsg = "�A�j���[�V�����C�x���g���������Ă΂�Ă��܂���B : ";
					errorMsg += animationEventName;

					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
				}
			}
		}
	}
}