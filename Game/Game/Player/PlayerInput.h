#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayerAction;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}

	namespace nsPlayer {

		//プレイヤーの入力からアクションを起こすクラス
		class CPlayerInput : nsUtils::SNoncopyable
		{
		public:
			void Init(CPlayerAction* playerAction, nsPlayerAnimation::CPlayerAnimation* playerAnimation);

			void Update(bool isAnimationPlaying);

			void InputEnable() {

				//入力を許可する。
				m_canInput = true;
			}
		private:
			void InputSkillAction();
		private:
			CPlayerAction* m_playerAction = nullptr;	//プレイヤーアクションのポインタ
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;	//プレイヤーアニメーションのポインタ
			bool m_canInput = false;						//入力できる？
		};
	}
}

