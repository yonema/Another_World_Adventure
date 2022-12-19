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

			private:
				CPlayerInput* m_playerInput = nullptr;	//�v���C���[���̓N���X
			};
		}
	}
}