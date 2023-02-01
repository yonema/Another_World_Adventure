#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

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
#include "PlayerManager.h"
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

				//次のアイテムを選ぶ。
				if (Input()->IsTrigger(EnActionMapping::enItemSelectRight)) {

					m_playerAction->AddSelectItemNum();
				}

				//前のアイテムを選ぶ。
				if (Input()->IsTrigger(EnActionMapping::enItemSelectLeft)) {

					m_playerAction->SubSelectItemNum();
				}
			}

			//スキル準備入力がされていないかつ
			if (!Input()->IsPress(EnActionMapping::enSkillPreparation)) {

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

				//アクティブスキルを設定。
				CPlayerManager playerManager;
				if (playerManager.FindPlayer()) {
					std::list<nsSkill::SActiveSkillData> list = playerManager.GetCanUseActiveSkillList();
					playerManager.SetActiveSkill(0, "JumpAttack");
				}

				////クールタイム中に設定。
				//CoolTimeOn();
				//
				////スキル１使用。
				//m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_1);

				
#endif 
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				//スキル２使用。
#ifdef _DEBUG
				//アクティブスキルを設定。
				CPlayerManager playerManager;
				if (playerManager.FindPlayer()) {

					playerManager.SetActiveSkill(0, "SwordAttack");
				}

				////パッシブスキル（麻痺）を生成。
				//{
				//	//麻痺機能を生成。
				//	nsFeature::nsStatusChanger::CAbnormalStatus* paralysis = new nsFeature::nsStatusChanger::CAbnormalStatus;
				//	paralysis->Init(
				//		nsFeature::nsStatusChanger::EnAbnormalStatusType::enParalysis,
				//		player,
				//		1
				//	);
				//	//パッシブスキルに機能を追加。
				//	nsSkill::CPassiveSkill* passiveSkill = new nsSkill::CPassiveSkill;
				//	passiveSkill->AddFeature(paralysis);

				//	//プレイヤーにパッシブスキルを設定。
				//	player->GetPassiveSkillManager()->AddPassiveSkill(passiveSkill);
				//}
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

				//スキル３使用。

#ifdef _DEBUG
				//アイテム（毒）を生成。
				{
					//アイテムを仮生成。
					nsItem::CThrowItem* item = NewGO<nsItem::CThrowItem>();

					//毒機能を生成。
					nsFeature::nsStatusChanger::CAbnormalStatus* poison = new nsFeature::nsStatusChanger::CAbnormalStatus;
					poison->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
						player,
						1
					);

					//投げ開始座標を設定。
					item->SetStartPosition(player->GetPosition());
					item->SetThrowDirection(player->GetForwardDirection());

					//アイテムに機能を追加。
					//item->AddFeature(poison);

					//アイテムを追加。
					//player->GetItemManager()->AddItem(item);
				}
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_4)) {

				//スキル４使用。

#ifdef _DEBUG
				//プレイヤーにアイテムを与える。
				player->GetItemManager()->AddItem("ポーション", 2);
#endif
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