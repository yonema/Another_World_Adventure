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

				//�����N�G�X�g��i�߂�
				observablePlayer->ProgressSlayQuest(message);
			}
		}
	}
}