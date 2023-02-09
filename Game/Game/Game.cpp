#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "LoadGame.h"
#include "Samples/EffectSample.h"

#include "UI/Menu/MenuBaseUI.h"


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
		TestMenu();
	}

	void CGame::OnDestroy()
	{
		DeleteGO(m_menuBaseUI);
	}

	void CGame::TestMenu()
	{
		if (false == Input()->IsTrigger(EnActionMapping::enMenu)) {
			return;
		}

		if (true == m_flagCreateMenuBaseUI) {
			TestDeleteMenu();
			
			return;
		}

		m_menuBaseUI = NewGO<nsUI::CMenuBaseUI>();
		m_menuBaseUI->LoadLevel();

		m_flagCreateMenuBaseUI = true;
	}

	void CGame::TestDeleteMenu()
	{
		DeleteGO(m_menuBaseUI);

		m_flagCreateMenuBaseUI = false;
	}
}
