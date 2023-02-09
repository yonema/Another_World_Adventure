#include "YonemaEnginePreCompile.h"
#include "ObservablePlayer.h"
#include "PlayerObserver.h"
#include "../Player.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			void CObservablePlayer::AddObserver(CPlayerObserver* observer) {

				//オブザーバーを追加。
				m_observerList.emplace_back(observer);

				//初期化。
				observer->Init(this);
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

			void CObservablePlayer::NotifyObserver() {

				//各オブザーバーに通知。
				for (const auto& observer : m_observerList) {

					//更新。
					observer->Update(this);
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
		}
	}
}