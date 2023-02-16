#pragma once
#include "PlayerObserver.h"

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

				void AddObserver(CPlayerObserver* observer, EnObserverEvent observerEvent = EnObserverEvent::enNone);

				void ReleaseObserver();

				void NotifyObserver(EnObserverEvent observerEvent,const std::string& message = "");

				EnObserverEvent GetCarentEvent()const {

					//現在のイベントを取得。
					return m_carentEvent;
				}

			private:
				CPlayer* m_player = nullptr;				//プレイヤー
				EnObserverEvent m_carentEvent = EnObserverEvent::enNone;	//現在のイベント
				std::list<CPlayerObserver*> m_observerList;	//オブザーバーのリスト



			/*------以下オブザーバーに提供する関数------*/
			public:
				int GetExp()const;

				void SetLevel(int level);

				int GetLevel()const;

				const CVector3& GetPlayerPosition()const;

				void InputEnableBySystem();

				void InputDisableBySystem();

				void ProgressSlayQuest(const std::string& slayMonsterName);
			};
		}
	}
}

