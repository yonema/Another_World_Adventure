#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"
#include "PlayerManager.h"

#ifdef _DEBUG
#include "../Player/Player.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Feature/ApplyDamageFeature.h"
#include "../Feature/HealFeature.h"
#include "../Skill/PassiveSkill.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/ActiveSkill.h"
#include "../Item/SelfItem.h"
#include "../Item/ThrowItem.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Item/ItemManager.h"
#include "../CSV/CSVManager.h"
#include "../UserData.h"
#include "../Magic/MagicBallOne.h"
#endif

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

			//クールタイム中なら早期リターン。
			if (m_isCoolTime) { return; }

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
				}
				//アニメーションが再生されていないなら。
				else{

					//待機状態に設定し、このフレームは待機アニメーションが流れるようにする。
					m_playerAction->SetState(EnPlayerState::enIdle);
				}
			}

			//スキル準備入力。
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//各スキル使用への入力を受付。
				InputSkillAction();
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
				}

				//前のアイテムを選ぶ。
				if (Input()->IsTrigger(EnActionMapping::enItemSelectLeft)) {

					itemManager->BackItem();
				}
			}

			//R1,L1がともに押されていないなら。
			if (!Input()->IsPress(EnActionMapping::enSkillPreparation)
				&& !Input()->IsPress(EnActionMapping::enItemSelectPreparation)
				) {

				//弱攻撃入力。
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {

					//クールタイムをONにする。
					CoolTimeOn();

					//弱攻撃状態にする。
					m_playerAction->SetState(EnPlayerState::enWeakAttack);
				}

				//強攻撃入力。
				if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

					//クールタイムをONにする。
					CoolTimeOn();

					//強攻撃状態にする。
					m_playerAction->SetState(EnPlayerState::enStrongAttack);
				}

				//ステップ入力。
				if (Input()->IsTrigger(EnActionMapping::enStep)
					) {

					//クールタイムをONにする。
					CoolTimeOn();

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

#ifdef _DEBUG
			//プレイヤーを探す。
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);
#endif

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {
#ifdef _DEBUG

				CPlayerManager::GetInstance()->SetPassiveSkill(0,"ATKUp");

				////クールタイム中に設定。
				//CoolTimeOn();
				//
				////スキル１使用。
				//m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_1);
#endif 
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				CPlayerManager::GetInstance()->SetPassiveSkill(1, "ATKUp");
				////クールタイム中に設定。
				//CoolTimeOn();
				//
				////スキル２使用。
				//m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_2);
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

				CPlayerManager::GetInstance()->SetPassiveSkill(0, "Paralysiser");

				////クールタイム中に設定。
				//CoolTimeOn();
				//
				////スキル３使用。
				//m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_3);
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_4)) {

				//クールタイム中に設定。
				CoolTimeOn();

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