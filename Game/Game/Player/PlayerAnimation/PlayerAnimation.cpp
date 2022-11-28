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
			};

			void CPlayerAnimation::Init() {

				//各アニメーションを割り当てる。
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;

				//アニメーションを初期化。
				m_sAnimationInitData = new SAnimationInitData(
					static_cast<unsigned int>(EnAnimName::enNum),
					m_kAnimFilePaths
				);
			}

			void CPlayerAnimation::Release() {

				//アニメーションのデータを破棄。
				if (m_sAnimationInitData != nullptr) {

					delete m_sAnimationInitData;
					m_sAnimationInitData = nullptr;
				}
			}

			void CPlayerAnimation::UpdateAnimation(EnPlayerState playerState) {

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