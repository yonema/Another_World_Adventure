#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "Player.h"
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
			}

			//スキル準備入力。
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//各スキル使用への入力を受付。
				InputSkillAction();
			}

			//強攻撃入力。
			if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

				//強攻撃。
				m_playerAction->StrongAttack();
			}

#ifdef _DEBUG
			//プレイヤーを検索。
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
			if (player != nullptr) {

				auto sp = FindGO<CSpriteRenderer>("sampleSprite");
				if (sp != nullptr) {

					float playerSP = static_cast<float>(player->GetStatus()->GetSP());
					playerSP = playerSP / 100.0f;
					sp->SetScale({ playerSP ,playerSP ,playerSP });
				}
			}
#endif
		}

		void CPlayerInput::InputSkillAction() {

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {

#ifdef _DEBUG
				//デバッグ用にサンプルスプライトを生成。
				if (FindGO<CSpriteRenderer>("sampleSprite") == nullptr) {
					SSpriteInitData sampleSpriteData;
					sampleSpriteData.filePath = "Assets/Images/200x200PNG.png";
					sampleSpriteData.spriteSize = { 300.0f,300.0f };
					auto sampleSprite = NewGO<CSpriteRenderer>("sampleSprite");
					sampleSprite->Init(sampleSpriteData);
					sampleSprite->SetScale(1.0f);
				}
#endif
				//スキル１使用。
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				//スキル２使用。
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