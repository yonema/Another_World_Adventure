#pragma once
#include "PlayerAction.h"

namespace nsAWA {

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

