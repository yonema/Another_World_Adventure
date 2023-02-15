#include "YonejiTestScene.h"
#include "TitleScene.h"
#include "../World/World.h"
#include "../LoadGame.h"
#include "../GamePreLoading.h"
#include "../Event/EventController.h"
#include "../Event/EventManager.h"
#include "../Event/EventFlow.h"
#include "../Player/Player.h"
#include "../Camera/CameraAction.h"

// ÇªÇÃÇ§Çøè¡Ç∑ó\íË

namespace nsAWA
{
	namespace nsScene
	{
		bool CYonejiTestScene::Start()
		{

			m_world = NewGO<nsWorld::CWorld>();

			if (m_isTutorial)
			{
				m_world->SetMode(nsWorld::CWorld::EnMode::enTutorial);
			}

			return true;
		}

		void CYonejiTestScene::Update(float deltaTime)
		{
			if (Keyboard()->IsTrigger(EnKeyButton::enEscape))
			{
				CreateSceneWithFade<CTitleScene>();
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
			m_isLoaded = true;
			m_loadGame = NewGO<CLoadGame>();
			m_loadGame->SetPlayerSpawnPosition(m_world->GetPlayerSpawnPosition());
			m_loadGame->SetPlayerSpawnRotation(m_world->GetPlayerSpawnRotation());

			CVector3 addCameraVec = nsCamera::CCameraAction::GetStartAddCameraVec();
			m_world->GetPlayerSpawnRotation().Apply(addCameraVec);
			nsCamera::CCameraAction::SetStartAddCameraVec(addCameraVec);
			


			return;
		}




	}
}