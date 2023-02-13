#include "YonejiTestScene.h"
#include "TitleScene.h"
#include "../World/World.h"
#include "../LoadGame.h"

// ‚»‚Ì‚¤‚¿Á‚·—\’è

namespace nsAWA
{
	namespace nsScene
	{
		bool CYonejiTestScene::Start()
		{
			constexpr float kFarClip = 5000.0f;
			MainCamera()->SetFarClip(kFarClip);

			m_world = NewGO<nsWorld::CWorld>();

			return true;
		}

		void CYonejiTestScene::Update(float deltaTime)
		{
			if (Keyboard()->IsTrigger(EnKeyButton::enEscape))
			{
				CreateScene<CTitleScene>();
			}

			InitAfterBaseLoaded(deltaTime);

			return;
		}

		void CYonejiTestScene::OnDestroy()
		{
			DeleteGO(m_world);
			m_world = nullptr;

			DeleteGO(m_loadGame);
			m_loadGame = nullptr;

			return;
		}

		void CYonejiTestScene::InitAfterBaseLoaded(float deltaTime)
		{
			if (m_loadGame != nullptr || m_world->IsLevelLoaded() != true)
			{
				return;
			}

			m_loadGame = NewGO<CLoadGame>();

			return;
		}




	}
}