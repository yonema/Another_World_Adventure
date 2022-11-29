#pragma once
#include "PlayerAnimationBase.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//プレイヤーの剣アニメーション
			class CPlayerSwordAnimation : public CPlayerAnimationBase
			{
				void UpdateAnimation(CModelRenderer* playerModel, EnPlayerState playerState)override final;
			};
		}
	}
}

