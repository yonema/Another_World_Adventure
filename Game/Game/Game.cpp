#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "LoadGame.h"


namespace nsAWA
{
	const char* const CGame::m_kGameObjectName = "Game";

	bool CGame::Start()
	{
		//ゲームをロード。
		NewGO<CLoadGame>();

		return true;
	}

	void CGame::Update(float deltaTime)
	{

	}

	void CGame::OnDestroy()
	{

	}
}
