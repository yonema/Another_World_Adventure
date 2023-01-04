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

			void CoolTimeOn() {

				//�N�[���^�C�����ɂ���B
				m_isCoolTime = true;
			}

			void CoolTimeOff() {

				//�N�[���^�C�����O���B
				m_isCoolTime = false;
			}

			bool GetCoolTime()const {

				return m_isCoolTime;
			}

			void ChangeState();

		private:
			void InputSkillAction();

		private:
			CPlayerAction* m_playerAction = nullptr;	//�v���C���[�A�N�V�����̃|�C���^
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;	//�v���C���[�A�j���[�V�����̃|�C���^
			bool m_isCoolTime = false;		//�N�[���^�C�����H
		};
	}
}

