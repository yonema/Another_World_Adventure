#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayerAction;
		class CPlayer;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}

	namespace nsPlayer {

		//�v���C���[�̓��͂���A�N�V�������N�����N���X
		class CPlayerInput : nsUtils::SNoncopyable
		{
		public:
			void Init(const CPlayer* player,CPlayerAction* playerAction, nsPlayerAnimation::CPlayerAnimation* playerAnimation);

			void Release() {};

			void Update(bool isAnimationPlaying);

			void InputEnable() {

				//���͂ł����Ԃɂ���B
				m_canInput = true;
			}

			void InputEnableBySystem() {

				//���͉\��Ԃɂ���B
				m_canInputBySystem = true;
			}

			void InputDisable() {

				//���͂ł��Ȃ���Ԃɂ���B
				m_canInput = false;
			}

			void InputDisableBySystem() {

				//���͂ł��Ȃ���Ԃɂ���B
				m_canInputBySystem = false;
			}

			void CoolTimeOn() {

				//�N�[���^�C��ON�B
				m_isCoolTime = true;
			}

			void CoolTimeOff() {

				//�N�[���^�C��OFF�B
				m_isCoolTime = false;
			}

			void ChangeState();

		private:
			void InputSkillAction();

		private:
			const CPlayer* m_player = nullptr;			//�v���C���[
			CPlayerAction* m_playerAction = nullptr;	//�v���C���[�A�N�V�����̃|�C���^
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;	//�v���C���[�A�j���[�V�����̃|�C���^
			bool m_canInput = true;		//���͂ł���H
			bool m_canInputBySystem = true;//�V�X�e���ɂ����͉\�t���O
			bool m_isCoolTime = false;	//�N�[���^�C�����H
			float m_magicTime = 0.0f;		//���@�X�L���̉r������
		};
	}
}

