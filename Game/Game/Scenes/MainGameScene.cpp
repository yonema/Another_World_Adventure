#include "MainGameScene.h"
#include "../LoadGame.h"

namespace nsAWA
{
	namespace nsScene
	{
		bool CMainGameScene::Start()
		{
			//�Q�[�������[�h�B
			NewGO<CLoadGame>();

			return true;
		}

		void CMainGameScene::Update(float deltaTime)
		{
			return;
		}

		void CMainGameScene::OnDestroy()
		{

			return;
		}
	}
}