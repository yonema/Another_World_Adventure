#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "Scenes/TitleScene.h"



namespace nsAWA
{
	const char* const CGame::m_kGameObjectName = "Game";

	bool CGame::Start()
	{
		nsScene::CreateScene<nsScene::CTitleScene>();

		return true;
	}

	void CGame::Update(float deltaTime)
	{

		return;
	}

	void CGame::OnDestroy()
	{
		nsScene::DeleteCurrentScene();

		return;
	}


}
