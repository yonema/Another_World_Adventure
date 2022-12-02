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
#include "../Item/ImmediatelyItem.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Item/ItemManager.h"
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

#ifdef _DEBUG
			//プレイヤーを探す。
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);

			//ダメージ機能を生成。
			nsFeature::CApplyDamageFeature* damage = new nsFeature::CApplyDamageFeature;
			damage->Init(
				12,			//レベル
				10,			//威力
				20,			//攻撃力
				14,			//防御力
				player,		//ターゲット
				false		//ガードできる？
			);

			//アクティブスキルに機能を追加。
			nsSkill::CActiveSkill* activeSkill = new nsSkill::CActiveSkill;
			activeSkill->AddFeature(damage);
			activeSkill->SetUseMP(30);

			//プレイヤーにアクティブスキルを追加。
			player->SetActiveSkill(EnActiveSkillListNumber::enActiveSkill_1, activeSkill);

			//入力可能に設定。
			m_canInput = true;
#endif
		}

		void CPlayerInput::Update(bool isAnimationPlaying) {

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
						m_playerAction->SetState(EnPlayerState::enDash);
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
				else if(!isAnimationPlaying){

					//待機状態に設定する。
					m_playerAction->SetState(EnPlayerState::enIdle);
				}
			}

			//スキル準備入力。
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//各スキル使用への入力を受付。
				InputSkillAction();
			}

			//弱攻撃入力。
			if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {

				//弱攻撃状態にする。
				m_playerAction->SetState(EnPlayerState::enWeakAttack_A);
			}

			//強攻撃入力。
			if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

				//強攻撃状態にする。
				m_playerAction->SetState(EnPlayerState::enStrongAttack);
			}

			//アイテム使用入力。
			if (Input()->IsTrigger(EnActionMapping::enUseItem)
				&& !Input()->IsPress(EnActionMapping::enItemSelectPreparation)
				&& !Input()->IsPress(EnActionMapping::enSkillPreparation)
				) {

				//アイテムを使用。
				m_playerAction->UseItem();
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

			//ガード準備入力。
			if (Input()->IsPress(EnActionMapping::enGuardPreparation)) {

				//ガード入力。
				if (Input()->IsPress(EnActionMapping::enGuard)) {

					//ガード。
					m_playerAction->Guard();
				}
			}

			//もしステートに変更があったら。
			if (m_playerAction->IsChangeState()) {

				//流すアニメーションを変更する。
				m_playerAnimation->PlayAnimation(m_playerAction->GetState());
			}
		}

		void CPlayerInput::InputSkillAction() {

#ifdef _DEBUG
			//プレイヤーを探す。
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);
#endif

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {
#ifdef _DEBUG
				//スキル１使用。
				m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_1);
#endif 
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				//スキル２使用。
#ifdef _DEBUG
				//パッシブスキル（麻痺）を生成。
				{
					//麻痺機能を生成。
					nsFeature::nsStatusChanger::CAbnormalStatus* paralysis = new nsFeature::nsStatusChanger::CAbnormalStatus;
					paralysis->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enParalysis,
						player,
						1
					);
					//パッシブスキルに機能を追加。
					nsSkill::CPassiveSkill* passiveSkill = new nsSkill::CPassiveSkill;
					passiveSkill->AddFeature(paralysis);

					//プレイヤーにパッシブスキルを設定。
					player->GetPassiveSkillManager()->AddPassiveSkill(passiveSkill);
				}
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

				//スキル３使用。

#ifdef _DEBUG
				//アイテム（毒）を生成。
				{
					//アイテムを仮生成。
					nsItem::CImmediatelyItem* item = NewGO<nsItem::CImmediatelyItem>();

					//毒機能を生成。
					nsFeature::nsStatusChanger::CAbnormalStatus* poison = new nsFeature::nsStatusChanger::CAbnormalStatus;
					poison->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
						player,
						1
					);

					//アイテムに機能を追加。
					item->AddFeature(poison);

					//アイテムを追加。
					player->GetItemManager()->AddItem(item);
				}
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_4)) {

				//スキル４使用。
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_5)) {

				//スキル５使用。
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_6)) {

				//スキル６使用。
			}
		}
	}
}