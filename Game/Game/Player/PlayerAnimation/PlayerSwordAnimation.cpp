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

				CPlayerAnimation::EnAnimName animNameRef = CPlayerAnimation::EnAnimName::enNone;

				//�X�e�[�g�ɉ����ăA�j���[�V�������Đ��B
				switch (playerState) {

					//�ҋ@�B
				case EnPlayerState::enIdle:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Idle;
					break;
					//�����B
				case EnPlayerState::enWalk:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Walk;
					break;
					//����B
				case EnPlayerState::enDash:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Dash;
					break;
					//��U��A�B
				case EnPlayerState::enWeakAttack_A:
				
					animNameRef = CPlayerAnimation::EnAnimName::enSword_WeakAttack_A;
					break;
				case EnPlayerState::enStrongAttack:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_StrongAttack;
					break;
				case EnPlayerState::enDamage:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Damage;
					break;
				case EnPlayerState::enDeath:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Death;
					break;
				case EnPlayerState::enGuard:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Guard;
					break;
				case EnPlayerState::enUseItem:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_UseItem;
					break;
				case EnPlayerState::enStun:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Stun;
					break;
				}

				//�A�j���[�V�������Đ��B
				playerModel->PlayAnimation(
					static_cast<unsigned int>(m_animDataList[static_cast<unsigned int>(animNameRef)].animName),
					m_animDataList[static_cast<unsigned int>(animNameRef)].speed,
					m_animDataList[static_cast<unsigned int>(animNameRef)].enLoopFlag
				);
			}
		}
	}
}