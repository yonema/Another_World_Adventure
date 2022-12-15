#include "YonemaEnginePreCompile.h"
#include "PlayerAnimation.h"
#include "PlayerAnimationBase.h"
#include "PlayerSwordAnimation.h"
#include "../PlayerInput.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//�A�j���[�V�����̃t�@�C���p�X���`�B
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

				//�e�A�j���[�V���������蓖�Ă�B
				m_playerAnimation[static_cast<int>(EnAnimType::enSword)] = new CPlayerSwordAnimation;

				//���̓N���X�̃|�C���^���擾�B
				m_playerInput = playerInput;
#ifdef _DEBUG
				//���^�C�v�ɐݒ�B
				m_type = EnAnimType::enSword;
#endif // _DEBUG

			}

			void CPlayerAnimation::SetPlayerModelAndAnimEvent(CModelRenderer* playerModel) {

				//�v���C���[���f����ݒ�B
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

				//�X�e�[�g�ɕύX�����������B
				if (changeState) {
					
					//�X�e�[�g�ɑΉ�����A�j���[�V�����𗬂��B
					PlayAnimation(playerState);
				}
			}

			void CPlayerAnimation::PlayAnimation(EnPlayerState playerState) {

				//�A�j���[�V�����^�C�v����ǂ̃A�j���[�V�����N���X���g�������߂�B
				switch (m_type) {

					//���A�j���[�V�����N���X�B
				case EnAnimType::enSword:

					//�X�V�B
					m_playerAnimation[static_cast<int>(EnAnimType::enSword)]->UpdateAnimation(m_playerModel, playerState);
					break;
				}
			}
		}
	}
}