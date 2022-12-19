#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayerInput;
	}

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//�v���C���[�A�j���[�V�����C�x���g�N���X
			class CPlayerAnimationEvent : nsUtils::SNoncopyable
			{
			public:
				void Init(CPlayerInput* playerInput) {

					//�e�|�C���^���i�[�B
					m_playerInput = playerInput;
				}

				void CoolTimeOn();

				void CoolTimeOff();

				void GetAnimationEvent(const std::string& animationEventName) {

					//�C�x���g�̖��O����Ή����郁���o�֐����Ăяo���B

					if (animationEventName == "CoolTimeOn") {

						CoolTimeOn();
					}
					else if (animationEventName == "CoolTimeOff") {

						CoolTimeOff();
					}
					else {

						nsGameWindow::MessageBoxWarning(L"�A�j���[�V�����C�x���g���Ɍ�肪����܂��B");
					}
				}

			private:
				CPlayerInput* m_playerInput = nullptr;	//�v���C���[���̓N���X
			};
		}
	}
}