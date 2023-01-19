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

			namespace {

				constexpr float kMoveSpeed = 60.0f;		//�A�N�e�B�u�X�L���ɂ��ړ����x
			}

			void CPlayerAnimationEvent::Update() {

				//�C�x���g�ɂ���ē����t���O�������Ă���Ȃ�B
				if (m_isMoving) {

					//�ړ�
					Move();
				}
			}

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

			void CPlayerAnimationEvent::CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr) {

				auto trigger = NewGO<CCreateTrigger>();
				trigger->Create(
					creator,
					animEventDataStr,
					m_playerAction->GetPosition(),
					m_playerAction->GetForwardDirection()
				);
			}

			void CPlayerAnimationEvent::MoveStart() {

				//�ړ��t���O��ON�B
				m_isMoving = true;
			}

			void CPlayerAnimationEvent::MoveEnd() {

				//�ړ��t���O��OFF�B
				m_isMoving = false;
			}

			void CPlayerAnimationEvent::Move() {

				//�O�������擾�B
				CVector3 forwardDirection = m_playerAction->GetForwardDirection();

				//�ړ��B
				m_playerAction->Move(forwardDirection.x, forwardDirection.z, kMoveSpeed);
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

					CreateTrigger(m_player,animationEventData);
				}
				else if (animationEventName == "MoveStart") {

					MoveStart();
				}
				else if (animationEventName == "MoveEnd") {

					MoveEnd();
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