#pragma once
#include "PlayerAnimationBase.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//�v���C���[�̌��A�j���[�V����
			class CPlayerSwordAnimation : public CPlayerAnimationBase
			{
				void UpdateAnimation(CModelRenderer* playerModel, EnPlayerState playerState)override final;
			};
		}
	}
}

