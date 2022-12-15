#include "YonemaEnginePreCompile.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"
#include "../PlayerInput.h"

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
				"Assets/Animations/Samples/Sword_UseItemTest.fbx",
				"Assets/Animations/Sword_Stun.fbx",
			};

			void CPlayerAnimation::Init(CPlayerInput* playerInput) {

				//各アニメーションを割り当てる。
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;

				//入力クラスのポインタを取得。
				m_playerInput = playerInput;
#ifdef _DEBUG
				//剣タイプに設定。
				m_type = EnAnimType::enSword;
#endif // _DEBUG

			}

			void CPlayerAnimation::SetPlayerModelAndAnimEvent(CModelRenderer* playerModel) {

				//プレイヤーモデルを設定。
				m_playerModel = playerModel;

				m_playerModel->ReserveAnimationEventFuncArray(static_cast<unsigned int>(EnAnimName::enSword_UseItem), 2);

				m_playerModel->AddAnimationEventFunc(
					static_cast<unsigned int>(EnAnimName::enSword_UseItem),
					[&]() {m_playerInput->CoolTimeOn(); }
				);

				m_playerModel->AddAnimationEventFunc(
					static_cast<unsigned int>(EnAnimName::enSword_UseItem),
					[&]() {m_playerInput->CoolTimeOff(); }
				);
			}

			void CPlayerAnimation::Release() {

			}

			void CPlayerAnimation::Update(bool changeState, EnPlayerState playerState) {

				//ステートに変更があったか。
				if (changeState) {
					
					//ステートに対応するアニメーションを流す。
					PlayAnimation(playerState);
				}
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