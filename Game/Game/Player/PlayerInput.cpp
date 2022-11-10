#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"

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
					//移動。
					m_playerAction->Move(
						inputX,
						inputZ
					);

					//回転。
					m_playerAction->Rotate();
				}
			}

#ifdef _DEBUG
			//仮にアクションボタン入力でHPダメージを受けるように。
			if (Input()->IsTrigger(EnActionMapping::enAction)) {

				//プレイヤーを検索。
				auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
				//40ダメージを与える。
				player->GetStatus()->DamageHP(40);
			}
#endif
		}
	}
}