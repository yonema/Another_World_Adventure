#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayerInput;
	}

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			//プレイヤーアニメーションイベントクラス
			class CPlayerAnimationEvent : nsUtils::SNoncopyable
			{
			public:
				void Init(CPlayerInput* playerInput) {

					//各ポインタを格納。
					m_playerInput = playerInput;
				}

				void CoolTimeOn();

				void CoolTimeOff();

			private:
				CPlayerInput* m_playerInput = nullptr;	//プレイヤー入力クラス
			};
		}
	}
}