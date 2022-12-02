#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayerAction;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}

	namespace nsPlayer {

		//�v���C���[�̓��͂���A�N�V�������N�����N���X
		class CPlayerInput : nsUtils::SNoncopyable
		{
		public:
			void Init(CPlayerAction* playerAction, nsPlayerAnimation::CPlayerAnimation* playerAnimation);

			void Update(bool isAnimationPlaying);

			void InputEnable() {

				//���͂�������B
				m_canInput = true;
			}
		private:
			void InputSkillAction();
		private:
			CPlayerAction* m_playerAction = nullptr;	//�v���C���[�A�N�V�����̃|�C���^
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;	//�v���C���[�A�j���[�V�����̃|�C���^
			bool m_canInput = false;						//���͂ł���H
		};
	}
}

