#include "YonemaEnginePreCompile.h"
#include "../PlayerAction.h"
#include "../PlayerInput.h"
#include "PlayerAnimation.h"
#include "PlayerSwordAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			void CPlayerSwordAnimation::UpdateAnimation(CModelRenderer* playerModel, EnPlayerState playerState) {

				//現在のアニメーションの再生状況を取得する。
				m_isPlaying = playerModel->IsPlaying();

				CPlayerAnimation::EnAnimName animNameRef = CPlayerAnimation::EnAnimName::enNone;

				//ステートに応じてアニメーションを再生。
				switch (playerState) {

					//待機。
				case EnPlayerState::enIdle:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Idle;
					break;
					//歩く。
				case EnPlayerState::enWalk:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Walk;
					break;
					//走る。
				case EnPlayerState::enDash:

					animNameRef = CPlayerAnimation::EnAnimName::enSword_Dash;
					break;
					//弱攻撃A。
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

				//アニメーションを再生。
				playerModel->PlayAnimation(
					static_cast<unsigned int>(m_animDataList[static_cast<unsigned int>(animNameRef)].animName),
					m_animDataList[static_cast<unsigned int>(animNameRef)].speed,
					m_animDataList[static_cast<unsigned int>(animNameRef)].enLoopFlag
				);
			}
		}
	}
}