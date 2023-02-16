#include "YonemaEnginePreCompile.h"
#include "ObservablePlayer.h"
#include "PlayerObserver.h"
#include "../Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			void CObservablePlayer::AddObserver(CPlayerObserver* observer, EnObserverEvent observerEvent) {

				//オブザーバーを追加。
				m_observerList.emplace_back(observer);

				//初期化。
				observer->Init(this, observerEvent);
			}

			void CObservablePlayer::ReleaseObserver() {

				//破棄処理を実行。
				for (auto itr = m_observerList.begin(); itr != m_observerList.end(); ) {

					//破棄。
					(*itr)->Release();
					itr = m_observerList.erase(itr);

					//破棄されたことにより、既に次のイテレータが入っているので移る処理をスキップ。
					continue;
				}
			}

			void CObservablePlayer::NotifyObserver(EnObserverEvent observerEvent,const std::string& message) {

				//イベントを取得。
				m_carentEvent = observerEvent;

				//各オブザーバーに通知。
				for (const auto& observer : m_observerList) {

					//イベントリストを順に参照。
					for (auto observerEventData : observer->GetEventList()) {

						//イベントが一致したら。
						if (observerEventData == observerEvent) {

							//更新。
							observer->Update(this,message);

							//このオブザーバーは更新したので終了。
							break;
						}
					}
				}
			}

			/*------以下オブザーバーに提供する関数------*/

			int CObservablePlayer::GetExp()const {

				//経験値を取得。
				return m_player->GetStatus()->GetExp();
			}

			void CObservablePlayer::SetLevel(int level) {

				//レベルを設定。
				m_player->GetStatus()->SetLevel(level);
			}

			int CObservablePlayer::GetLevel()const {

				//レベルを取得。
				return m_player->GetStatus()->GetLevel();
			}

			void CObservablePlayer::InputEnableBySystem() {

				//入力できる状態にする。
				m_player->InputEnableBySystem();
			}

			void CObservablePlayer::InputDisableBySystem() {

				//入力できない状態にする。
				m_player->InputDisableBySystem();
			}

			void CObservablePlayer::ProgressSlayQuest(const std::string& slayMonsterName)
			{
				//討伐クエストを進める
				m_player->ProgressSlayQuest(slayMonsterName);
			}

			const CVector3& CObservablePlayer::GetPlayerPosition()const {

				//プレイヤーの座標を取得。
				return m_player->GetPosition();
			}
		}
	}
}