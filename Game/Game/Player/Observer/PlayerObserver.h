#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//前方宣言
		namespace nsObserver {

			class CObservablePlayer;
		}

		namespace nsObserver {

			//通知の抽象クラス
			class CPlayerObserver : nsUtils::SNoncopyable
			{
			public:
				virtual void Init(CObservablePlayer* observablePlayer) {};

				void Release() {

					//派生クラスの破棄処理を実行。
					ReleaseSub();

					//自身を破棄。
					delete this;
				}

				virtual void ReleaseSub() {};

				virtual void Update(CObservablePlayer* observablePlayer) = 0;
			};
		}
	}
}