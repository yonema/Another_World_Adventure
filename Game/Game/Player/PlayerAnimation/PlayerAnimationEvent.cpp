#include "YonemaEnginePreCompile.h"
#include "PlayerAnimationEvent.h"
#include "../../GameActor.h"
#include "../PlayerInput.h"
#include "../PlayerAction.h"
#include "PlayerAnimation.h"
#include "../../CreateTrigger.h"
#include "../../Skill/ActiveSkill.h"
#include "../../Skill/ActiveSkillList.h"
#include "../../Magic/MagicList.h"
#include "../../Magic/MagicBase.h"

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

				//入力不可に設定。
				m_playerInput->InputDisable();

				//クールタイムON。
				m_playerInput->CoolTimeOn();
			}

			void CPlayerAnimationEvent::CoolTimeOff() {

				//入力可能に設定。
				m_playerInput->InputEnable();

				//クールタイムOFF。
				m_playerInput->CoolTimeOff();

				//ステートを初期化する。
				m_playerInput->ChangeState();
			}

			void CPlayerAnimationEvent::InputEnable() {

				//入力可能に設定。
				m_playerInput->InputEnable();
			}

			void CPlayerAnimationEvent::CreateTrigger(const std::string& triggerIndexStr) {

				std::list<std::vector<std::string>> triggerMaterialStr;

				//スキル使用中なら、そのスキルのアニメーションイベントデータを取得。
				if (m_playerAction->GetState() == EnPlayerState::enUseActiveSkill) {

					nsSkill::CActiveSkill* activeSkill = m_playerAnimation->GetReserveActiveSkillInfo();

					nsSkill::CActiveSkill::SActiveSkillAnimData activeSkillAnimData = activeSkill->GetActiveSkillAnimData(triggerIndexStr);
					triggerMaterialStr = activeSkillAnimData.sAnimEventData;
				}
				else {

					//通常攻撃。
					std::string attackName = "NoName";

					//現在のステートから文字列を取得。
					switch (m_playerAction->GetState()) {

					case EnPlayerState::enWeakAttack_A:
						attackName = "WeakAttack_A";
						break;
					case EnPlayerState::enWeakAttack_B:
						attackName = "WeakAttack_B";
						break;
					case EnPlayerState::enWeakAttack_C:
						attackName = "WeakAttack_C";
						break;
					case EnPlayerState::enStrongAttack:
						attackName = "StrongAttack";
						break;
					default:
						break;
					}

					//通常攻撃のアニメーションイベントデータを取得。
					nsSkill::SActiveSkillData attack = nsSkill::CActiveSkillList::GetInstance()->GetActiveSkillData(attackName);

					for (const auto& data : attack.animDataList) {

						if (data.index == triggerIndexStr) {

							//設定。
							triggerMaterialStr = data.sAnimEventData;
						}
					}
				}

				//トリガーを生成。
				auto trigger = NewGO<CCreateTrigger>();
				trigger->Create(
					m_player,
					triggerMaterialStr,
					m_player->GetPosition(),
					m_player->GetForwardDirection()
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

					//プレイヤーの前方向を取得。
					const auto& playerDir = m_player->GetForwardDirection();

					//カメラの前方向を取得。
					const auto& camDir = MainCamera()->GetForwardDirection();

					//回転を適用。
					CQuaternion rot;
					rot.SetRotation(camDir, playerDir);
					m_playerMoveInput = CVector3::Front();
					rot.Apply(m_playerMoveInput);
					m_playerMoveInput.Normalize();
				}
			}

			void CPlayerAnimationEvent::CreateMagic() {

				//現在使用中の魔法スキルの名前を取得する。
				std::string magicName = m_playerAnimation->GetReserveActiveSkillInfo()->GetName();

				//魔法を生成。
				nsMagic::CMagicBuilder magicBuilder;
				auto magic = magicBuilder.CreateMagic(magicName);

				//発動者を設定。
				magic->SetOwner(m_player);

				//座標を設定。
				magic->SetPosition(m_player->GetPosition());

				//射出方向を設定。
				magic->SetMoveDirection(m_player->GetForwardDirection());
			}

			void CPlayerAnimationEvent::GetAnimationEvent(const std::string& animationEventName, const std::string& detailStr) {

				//イベントの名前から対応するメンバ関数を呼び出す。

				if (animationEventName == "CoolTimeOn") {

					CoolTimeOn();
				}
				else if (animationEventName == "CoolTimeOff") {

					CoolTimeOff();
				}
				else if (animationEventName == "CreateTrigger") {

					CreateTrigger(detailStr);
				}
				else if (animationEventName == "MoveStart") {

					MoveStart();
				}
				else if (animationEventName == "MoveEnd") {

					MoveEnd();
				}
				else if (animationEventName == "CreateMagic") {

					CreateMagic();
				}
				else if (animationEventName == "InputEnable") {

					InputEnable();
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