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

				constexpr float kMoveSpeed = 60.0f;		//アクティブスキルによる移動速度
			}

			void CPlayerAnimationEvent::Update() {

				//イベントによって動くフラグが立っているなら。
				if (m_isMoving) {

					//移動
					Move();
				}
			}

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

				//移動フラグをON。
				m_isMoving = true;
			}

			void CPlayerAnimationEvent::MoveEnd() {

				//移動フラグをOFF。
				m_isMoving = false;
			}

			void CPlayerAnimationEvent::Move() {

				//前方向を取得。
				CVector3 forwardDirection = m_playerAction->GetForwardDirection();

				//移動。
				m_playerAction->Move(forwardDirection.x, forwardDirection.z, kMoveSpeed);
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

					CreateTrigger(m_player,animationEventData);
				}
				else if (animationEventName == "MoveStart") {

					MoveStart();
				}
				else if (animationEventName == "MoveEnd") {

					MoveEnd();
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