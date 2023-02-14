#pragma once
#include "../PlayerObserver.h"

namespace nsAWA
{
	namespace nsPlayer
	{
		namespace nsObserver
		{
			class CPlayerSlayQuestObserver : public CPlayerObserver
			{
				void Update(CObservablePlayer* observablePlayer)override final;
			};
		}
	}
}

