#include "YonemaEnginePreCompile.h"
#include "PlayerSlayQuestObserver.h"
#include "../ObservablePlayer.h"

namespace nsAWA
{
	namespace nsPlayer
	{
		namespace nsObserver
		{
			void CPlayerSlayQuestObserver::Update(CObservablePlayer* observablePlayer) {

				//�����N�G�X�g��i�߂�
				observablePlayer->ProgressSlayQuest();
			}
		}
	}
}