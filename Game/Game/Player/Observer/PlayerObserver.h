#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//前方宣言
		namespace nsObserver {

			class CObservablePlayer;
		}

		namespace nsObserver {

			//オブザーバーのイベント
			enum class EnObserverEvent {

				enWin,	//勝利したとき
				enInputEnable,	//プレイヤーの入力を受け付ける
				enInputDisable,//プレイヤーの入力を受け付けない

				enNone = -1	//設定なし
			};

			//通知の抽象クラス
			class CPlayerObserver : nsUtils::SNoncopyable
			{
			public:
				void Init(CObservablePlayer* observablePlayer, EnObserverEvent observerEvent) {

					//イベントが設定されていたら。
					if (observerEvent != EnObserverEvent::enNone) {
						//イベントを追加。
						AddEvent(observerEvent);
					}

					//派生クラスを初期化。
					InitSub(observablePlayer);
				}

				virtual void InitSub(CObservablePlayer* observablePlayer) {};

				void Release() {

					//派生クラスの破棄処理を実行。
					ReleaseSub();

					//自身を破棄。
					delete this;
				}

				virtual void ReleaseSub() {};

				virtual void Update(CObservablePlayer* observablePlayer) = 0;

				void AddEvent(EnObserverEvent observerEvent) {

					//イベントを追加。
					m_observerEventList.emplace_back(observerEvent);
				}

				std::list<EnObserverEvent> GetEventList()const {

					//イベントリストを取得。
					return m_observerEventList;
				}

			private:
				std::list<EnObserverEvent> m_observerEventList;	//オブザーバーのイベントリスト
			};
		}
	}
}