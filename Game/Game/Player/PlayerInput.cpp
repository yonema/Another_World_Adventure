#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"
#include "PlayerManager.h"


namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kCanPlayerMoveInput = 0.001f;	//移動入力が判定される最低値
		}

		void CPlayerInput::Init(CPlayerAction* playerAction, nsPlayerAnimation::CPlayerAnimation* playerAnimation) {

			//入力によって行動させるため、プレイヤーアクションクラスのポインタを受け取る。
			m_playerAction = playerAction;

			//ステートを変化させるとともにアニメーションを再生するため、プレイヤーアニメーションクラスのポインタを受け取る。
			m_playerAnimation = playerAnimation;
		}

		void CPlayerInput::Update(bool isAnimationPlaying) {

			//入力できない状態なら早期リターン。
			if (!m_canInput) { return; }

			//移動・回転入力。
			{
				//入力を受け取る。
				auto inputX = Input()->GetVirtualAxis(EnAxisMapping::enRight);
				auto inputZ = Input()->GetVirtualAxis(EnAxisMapping::enForward);
				
				//入力がされているか。
				if (std::fabsf(inputX) > kCanPlayerMoveInput
					|| std::fabsf(inputZ) > kCanPlayerMoveInput
				)
				{
					//ダッシュ準備入力がされているか。
					if (Input()->IsPress(EnActionMapping::enDashPreparation)) {

						//ダッシュ状態にする。
						m_playerAction->SetState(EnPlayerState::enRun);
					}
					else {
						//歩き状態にする。
						m_playerAction->SetState(EnPlayerState::enWalk);
					}

					//移動。
					m_playerAction->Move(
						inputX,
						inputZ
					);

					//回転。
					m_playerAction->Rotate();

					//クールタイムOFF。
					CoolTimeOff();
				}
				//アニメーションが再生されていないなら。
				else if(!m_isCoolTime){

					//待機状態に設定し、このフレームは待機アニメーションが流れるようにする。
					m_playerAction->SetState(EnPlayerState::enIdle);
				}
			}

			//スキル準備入力。
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//各スキル使用への入力を受付。
				InputSkillAction();

				// UIの表示切替
				CPlayerManager::GetInstance()->ChangeFromItemToSkillUI();
			}

			//アイテム選択準備。
			if (Input()->IsPress(EnActionMapping::enItemSelectPreparation)
				&& !Input()->IsPress(EnActionMapping::enSkillPreparation)
				) {

				//アイテム管理クラスを取得。
				auto itemManager = CPlayerManager::GetInstance()->GetItemManager();

				//次のアイテムを選ぶ。
				if (Input()->IsTrigger(EnActionMapping::enItemSelectRight)) {

					itemManager->NextItem();
					// UIの表示切替
					CPlayerManager::GetInstance()->MoveNextItemUI();
				}

				//前のアイテムを選ぶ。
				if (Input()->IsTrigger(EnActionMapping::enItemSelectLeft)) {

					itemManager->BackItem();
					// UIの表示切替
					CPlayerManager::GetInstance()->MoveBackItemUI();
				}

				// UIの表示切替
				CPlayerManager::GetInstance()->ChangeFromSkillToItemUI();
			}

			//R1,L1がともに押されていないなら。
			if (!Input()->IsPress(EnActionMapping::enSkillPreparation)
				&& !Input()->IsPress(EnActionMapping::enItemSelectPreparation)
				) {

				//弱攻撃入力。
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {

					//入力不可に設定。
					InputDisable();

					if (m_playerAction->GetState() == EnPlayerState::enWeakAttack_A) {

						//弱攻撃B状態にする。
						m_playerAction->SetState(EnPlayerState::enWeakAttack_B);
					}
					else if (m_playerAction->GetState() == EnPlayerState::enWeakAttack_B) {

						//弱攻撃C状態にする。
						m_playerAction->SetState(EnPlayerState::enWeakAttack_C);
					}
					else {

						//弱攻撃A状態にする。
						m_playerAction->SetState(EnPlayerState::enWeakAttack_A);
					}
				}

				//強攻撃入力。
				if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

					//入力不可に設定。
					InputDisable();

					//強攻撃状態にする。
					m_playerAction->SetState(EnPlayerState::enStrongAttack);
				}

				//ステップ入力。
				if (Input()->IsTrigger(EnActionMapping::enStep)
					) {

					//入力不可に設定。
					InputDisable();

					//ステップ状態にする。
					m_playerAction->SetState(EnPlayerState::enStep);
				}

				//アイテム使用入力。
				if (Input()->IsTrigger(EnActionMapping::enUseItem)
					&& !Input()->IsPress(EnActionMapping::enItemSelectPreparation)
					&& !Input()->IsPress(EnActionMapping::enSkillPreparation)
					) {

					//アイテムを使用。
					m_playerAction->UseItem();
				}

				// UIの表示切替
				CPlayerManager::GetInstance()->ChangeFromItemToSkillUI();
			}

			//ガード準備入力。
			if (Input()->IsPress(EnActionMapping::enGuardPreparation)) {

				//ガード入力。
				if (Input()->IsPress(EnActionMapping::enGuard)) {

					//ガード。
					m_playerAction->Guard();
				}
			}
		}

		void CPlayerInput::InputSkillAction() {


			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {

				CPlayerManager::GetInstance()->SetActiveSkill(0,"JumpAttack_Sword");

				//クールタイム中に設定。
				CoolTimeOn();
				
				//スキル１使用。
				m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_1);
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				CPlayerManager::GetInstance()->SetActiveSkill(1, "JumpAttackL_Sword");

				//クールタイム中に設定。
				CoolTimeOn();
				
				//スキル２使用。
				m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_2);
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

				CPlayerManager::GetInstance()->SetPassiveSkill(0, "Paralysiser");

				////クールタイム中に設定。
				CoolTimeOn();
				
				//スキル３使用。
				m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_3);
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_4)) {

				//入力不可に設定。
				InputDisable();

				//スキル４使用。
				m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_4);
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_5)) {

				//スキル５使用。
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_6)) {

				//スキル６使用。
			}
		}

		void CPlayerInput::ChangeState() {

			//ステート状況を変更する。
			m_playerAction->ChangeState();
		}
	}
}