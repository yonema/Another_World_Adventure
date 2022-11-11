#pragma once
#include "PlayerAction.h"

namespace nsAWA {

	namespace nsPlayer {

		//プレイヤーの入力からアクションを起こすクラス
		class CPlayerInput : nsUtils::SNoncopyable
		{
		public:
			void Init(CPlayerAction* playerAction);

			void Update();
		private:
			void InputSkillAction();
		private:
			CPlayerAction* m_playerAction = nullptr;	//プレイヤーアクションのポインタ
		};
	}
}

