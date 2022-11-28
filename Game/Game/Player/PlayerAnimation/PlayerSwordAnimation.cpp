#include "YonemaEnginePreCompile.h"
#include "../PlayerAction.h"
#include "PlayerAnimation.h"
#include "PlayerSwordAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			void CPlayerSwordAnimation::UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) {

				//ステートに応じてアニメーションを再生。
				switch (playerState) {

					//待機。
				case EnPlayerState::enIdle:

					PlayerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Idle), 1.0f, true);
				}
			}
		}
	}
}