#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//前方宣言
		class CPlayer;
		namespace nsObserver {

			class CPlayerObserver;
		}

		namespace nsObserver {

			//オブザーバーを監視するクラス
			class CObservablePlayer : nsUtils::SNoncopyable
			{
			public:
				void Init(CPlayer* player) {

					//プレイヤーを獲得。
					m_player = player;
				}

				void AddObserver(CPlayerObserver* observer);

				void ReleaseObserver();

				void NotifyObserver();

			private:
				CPlayer* m_player = nullptr;				//プレイヤー
				std::list<CPlayerObserver*> m_observerList;	//オブザーバーのリスト



			/*------以下オブザーバーに提供する関数------*/
			public:
				int GetExp()const;

				void SetLevel(int level);

				int GetLevel()const;
			};
		}
	}
}

