#include "YonemaEnginePreCompile.h"
#include "PlayerInputObserver.h"
#include "../ObservablePlayer.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			void CPlayerInputObserver::Update(CObservablePlayer* observablePlayer, const std::string& message) {

				//���݂̃C�x���g���擾�B
				EnObserverEvent carentEvent = observablePlayer->GetCarentEvent();

				switch (carentEvent) {

				case EnObserverEvent::enInputEnable:

					//���͂ł����Ԃɂ���B
					observablePlayer->InputEnable();
					break;
				case EnObserverEvent::enInputDisable:

					//���͂ł��Ȃ���Ԃɂ���B
					observablePlayer->InputDisable();
					break;
				}
			}
		}
	}
}