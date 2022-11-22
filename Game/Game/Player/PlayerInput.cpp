#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "../Player/Player.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Feature/ApplyDamageFeature.h"
#include "../Feature/HealFeature.h"
#endif

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kCanPlayerMoveInput = 0.001f;	//移動入力が判定される最低値
		}

		void CPlayerInput::Init(CPlayerAction* playerAction) {

			//入力によって行動させるため、プレイヤーアクションクラスのポインタを受け取る。
			m_playerAction = playerAction;
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
				//ダメージ。
				nsFeature::CApplyDamageFeature damage;
				damage.Init(
					12,			//レベル
					10,			//威力
					20,			//攻撃力
					14,			//防御力
					player,		//ターゲット
					false		//ガードできる？
					);
				damage.Create();
#endif 
				//スキル１使用。
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {
#ifdef _DEBUG
				//回復。
				nsFeature::HealFeature heal;
				heal.Init(player, nsFeature::EnHealTarget::enHP, 100);
				heal.Create();
#endif

				//スキル２使用。
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {
#ifdef _DEBUG
				//毒。
				nsFeature::nsStatusChanger::CAbnormalStatus abnormalStatus;
				abnormalStatus.Init(
					nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
					player,
					1		//レベル
				);
				abnormalStatus.Create();
#endif
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