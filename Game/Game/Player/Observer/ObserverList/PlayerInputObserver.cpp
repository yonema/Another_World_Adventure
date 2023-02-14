#include "YonemaEnginePreCompile.h"
#include "PlayerInputObserver.h"
#include "../ObservablePlayer.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			void CPlayerInputObserver::Update(CObservablePlayer* observablePlayer, const std::string& message) {

				//現在のイベントを取得。
				EnObserverEvent carentEvent = observablePlayer->GetCarentEvent();

				switch (carentEvent) {

				case EnObserverEvent::enInputEnable:

					//入力できる状態にする。
					observablePlayer->InputEnable();
					break;
				case EnObserverEvent::enInputDisable:

					//入力できない状態にする。
					observablePlayer->InputDisable();
					break;
				}
			}
		}
	}
}