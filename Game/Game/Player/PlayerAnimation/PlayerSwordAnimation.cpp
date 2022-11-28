#include "YonemaEnginePreCompile.h"
#include "../PlayerAction.h"
#include "PlayerAnimation.h"
#include "PlayerSwordAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			void CPlayerSwordAnimation::UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) {

				//�X�e�[�g�ɉ����ăA�j���[�V�������Đ��B
				switch (playerState) {

					//�ҋ@�B
				case EnPlayerState::enIdle:

					PlayerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Idle), 1.0f, true);
				}
			}
		}
	}
}