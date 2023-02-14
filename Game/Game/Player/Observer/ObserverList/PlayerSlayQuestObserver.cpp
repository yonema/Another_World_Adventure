#include "YonemaEnginePreCompile.h"
#include "PlayerSlayQuestObserver.h"
#include "../ObservablePlayer.h"

namespace nsAWA
{
	namespace nsPlayer
	{
		namespace nsObserver
		{
			void CPlayerSlayQuestObserver::Update(CObservablePlayer* observablePlayer, const std::string& message) {

				//討伐クエストを進める
				observablePlayer->ProgressSlayQuest(message);
			}
		}
	}
}