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

				void GetAnimationEvent(const std::string& animationEventName) {

					//イベントの名前から対応するメンバ関数を呼び出す。

					if (animationEventName == "CoolTimeOn") {

						CoolTimeOn();
					}
					else if (animationEventName == "CoolTimeOff") {

						CoolTimeOff();
					}
					else {

						nsGameWindow::MessageBoxWarning(L"アニメーションイベント名に誤りがあります。");
					}
				}

			private:
				CPlayerInput* m_playerInput = nullptr;	//プレイヤー入力クラス
			};
		}
	}
}