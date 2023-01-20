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
				constexpr const float kCanPlayerMoveInput = 0.001f;	//移動入力が判定される最低値
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

				//入力を受け取る。
				m_playerMoveInput.x = Input()->GetVirtualAxis(EnAxisMapping::enRight);
				m_playerMoveInput.z = Input()->GetVirtualAxis(EnAxisMapping::enForward);

				//移動フラグをON。
				m_isMoving = true;
			}

			void CPlayerAnimationEvent::MoveEnd() {

				//入力情報を初期化。
				m_playerMoveInput.x = 0.0f;
				m_playerMoveInput.z = 0.0f;

				//移動フラグをOFF。
				m_isMoving = false;
			}

			void CPlayerAnimationEvent::Move() {

				//どの方向に入力されていたか。
				if (std::fabsf(m_playerMoveInput.x) > kCanPlayerMoveInput
					|| std::fabsf(m_playerMoveInput.z) > kCanPlayerMoveInput
				){
					//回転。
					m_playerAction->Rotate(
						false	//補間なし
					);

					//移動。
					m_playerAction->Move(m_playerMoveInput.x, m_playerMoveInput.z, kMoveSpeed);
				}
				else {

					//前方向を取得。
					m_playerMoveInput = m_playerAction->GetForwardDirection();

					//移動。
					m_playerAction->Move(m_playerMoveInput.x, m_playerMoveInput.z, kMoveSpeed);
				}
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