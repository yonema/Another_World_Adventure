#include "YonemaEnginePreCompile.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//アニメーションのファイルパスを定義。
			const char* CPlayerAnimation::
				m_kAnimFilePaths[static_cast<int>(EnAnimName::enNum)] =
			{
				"Assets/Animations/Sword_Idle.fbx",
				"Assets/Animations/Sword_Walk.fbx",
				"Assets/Animations/Sword_Dash.fbx",
				"Assets/Animations/Sword_WeakAttack_A.fbx",
				"Assets/Animations/Sword_StrongAttack.fbx",
				"Assets/Animations/Sword_Damage.fbx",
				"Assets/Animations/Sword_Death.fbx",
				"Assets/Animations/Sword_Guard.fbx",
				"Assets/Animations/Sword_UseItem.fbx",
			};

			void CPlayerAnimation::Init() {

				//各アニメーションを割り当てる。
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;

#ifdef _DEBUG
				//剣タイプに設定。
				m_type = EnAnimType::enSword;
#endif // _DEBUG

			}

			void CPlayerAnimation::Release() {

			}

			void CPlayerAnimation::Update() {

				
			}

			void CPlayerAnimation::PlayAnimation(EnPlayerState playerState) {

				//アニメーションタイプからどのアニメーションクラスを使うか決める。
				switch (m_type) {

					//剣アニメーションクラス。
				case EnAnimType::enSword:

					//更新。
					m_playerAnimation[static_cast<int>(EnAnimType::enSword)]->UpdateAnimation(m_playerModel, playerState);
					break;
				}
			}
		}
	}
}