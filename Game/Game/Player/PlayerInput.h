#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsPlayer {

		class CPlayerAction;
	}

	namespace nsPlayer {

		//�v���C���[�̓��͂���A�N�V�������N�����N���X
		class CPlayerInput : nsUtils::SNoncopyable
		{
		public:
			void Init(CPlayerAction* playerAction);

			void Update();
		private:
			void InputSkillAction();
		private:
			CPlayerAction* m_playerAction = nullptr;	//�v���C���[�A�N�V�����̃|�C���^
		};
	}
}

