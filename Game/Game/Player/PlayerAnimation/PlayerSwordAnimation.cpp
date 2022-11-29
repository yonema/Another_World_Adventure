#include "YonemaEnginePreCompile.h"
#include "../PlayerAction.h"
#include "../PlayerInput.h"
#include "PlayerAnimation.h"
#include "PlayerSwordAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			void CPlayerSwordAnimation::UpdateAnimation(CModelRenderer* playerModel, EnPlayerState playerState) {

				//���݂̃A�j���[�V�����̍Đ��󋵂��擾����B
				m_isPlaying = playerModel->IsPlaying();

				//�X�e�[�g�ɉ����ăA�j���[�V�������Đ��B
				switch (playerState) {

					//�ҋ@�B
				case EnPlayerState::enIdle:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Idle), 1.0f, true);
					break;
					//�����B
				case EnPlayerState::enWalk:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Walk), 1.0f, true);
					break;
					//����B
				case EnPlayerState::enDash:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Dash), 1.0f, true);
					break;
					//��U��A�B
				case EnPlayerState::enWeakAttack_A:
				
					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_WeakAttack_A), 1.0f, false);
					break;
				case EnPlayerState::enStrongAttack:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_StrongAttack), 1.0f, false);
					break;
				case EnPlayerState::enDamage:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Damage), 1.0f, false);
					break;
				case EnPlayerState::enDeath:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Death), 1.0f, false);
					break;
				case EnPlayerState::enGuard:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_Guard), 1.0f, true);
					break;
				case EnPlayerState::enUseItem:

					playerModel->PlayAnimation(static_cast<unsigned int>(CPlayerAnimation::EnAnimName::enSword_UseItem), 1.0f, false);
					break;
				}
			}
		}
	}
}