#include "MainGameScene.h"
#include "../LoadGame.h"
#include "../UI/Menu/MenuBaseUI.h"

namespace nsAWA
{
	namespace nsScene
	{
		bool CMainGameScene::Start()
		{
			//ゲームをロード。
			NewGO<CLoadGame>();

			return true;
		}

		void CMainGameScene::Update(float deltaTime)
		{
			TestMenu();

			return;
		}

		void CMainGameScene::OnDestroy()
		{
			DeleteGO(m_menuBaseUI);

			return;
		}

		void CMainGameScene::TestMenu()
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

		void CMainGameScene::TestDeleteMenu()
		{
			DeleteGO(m_menuBaseUI);

			m_flagCreateMenuBaseUI = false;
		}

	}
}