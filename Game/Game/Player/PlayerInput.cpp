#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "../Player/Player.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Feature/ApplyDamageFeature.h"
#include "../Feature/HealFeature.h"
#include "../Skill/PassiveSkill.h"
#include "../Skill/ActiveSkill.h"
#endif

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kCanPlayerMoveInput = 0.001f;	//移動入力が判定される最低値
		}

		void CPlayerInput::Init(CPlayerAction* playerAction) {

			//入力によって行動させるため、プレイヤーアクションクラスのポインタを受け取る。
			m_playerAction = playerAction;

#ifdef _DEBUG
			//プレイヤーを探す。
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);

			//毒機能を生成。
			nsFeature::nsStatusChanger::CAbnormalStatus* poison = new nsFeature::nsStatusChanger::CAbnormalStatus;
			poison->Init(
				nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
				player,
				1
			);

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
			activeSkill->AddFeature(poison);

			//プレイヤーにアクティブスキルを追加。
			player->SetActiveSkill(EnActiveSkillListNumber::enActiveSkill_1, activeSkill);
#endif
		}

		void CPlayerInput::Update() {

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
				else {

					//待機状態に設定する。
					m_playerAction->SetState(EnPlayerState::enIdle);
				}
			}

			//スキル準備入力。
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//各スキル使用への入力を受付。
				InputSkillAction();
			}

			//強攻撃入力。
			if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

				
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
			//プレイやーを探す。
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
				//毒機能を生成。
				nsFeature::nsStatusChanger::CAbnormalStatus* poison = new nsFeature::nsStatusChanger::CAbnormalStatus;
				poison->Init(
					nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
					player,
					1
				);
				//パッシブスキルに機能を追加。
				nsSkill::CPassiveSkill* passiveSkill = new nsSkill::CPassiveSkill;
				passiveSkill->AddFeature(poison);

				//プレイヤーにパッシブスキルを設定。
				player->AddPassiveSkill(passiveSkill);
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

				//スキル３使用。
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