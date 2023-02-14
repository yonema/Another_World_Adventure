#pragma once
#include "../PlayerObserver.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsObserver {

			class CPlayerInputObserver : public CPlayerObserver
			{
				void Update(CObservablePlayer* observablePlayer, const std::string& message)override final;
			};
		}
	}
}

