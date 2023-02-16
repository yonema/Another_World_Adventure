#include "EnterGameScene.h"
#include "../GamePreLoading.h"
#include "../GameNowLoading.h"
#include "../Event/EventController.h"
#include "../Event/EventNameTable.h"
#include "OpeningScene.h"
#include "YonejiTestScene.h"

namespace nsAWA
{
	namespace nsScene
	{

		bool CEnterGameScene::Start()
		{
			auto* eventFlow = CGamePreLoading::GetInstance()->
				GetEventController()->GetEventFlow(nsEvent::GetEventNameFromTable(
					nsEvent::EnEventNameType::enGoddesAndAWTransfer));

			if (eventFlow)
			{
				// OpeningÇ÷
				CreateScene<COpeningScene>();
			}
			else
			{
				// ÉQÅ[ÉÄÇ÷
				m_gameNowLoading = NewGO<CGameNowLoading>();

				InvokeFunc(
					[]()
					{
						auto* newScene = CreateScene<CYonejiTestScene>();
					},
					1.0f
						);


				m_gameNowLoading->SetExitFunc([]()->bool
					{
						auto* scene = ISceneBase::GetCurrentScene();
						auto* gameScene = dynamic_cast<CYonejiTestScene*>(scene);
						if (gameScene && gameScene->IsLoaded())
						{
							return true;
						}
						return false;
					}
				);
			}

			return true;
		}

		void CEnterGameScene::OnDestroy()
		{

			return;
		}

		void CEnterGameScene::Update(float deltaTime)
		{

			return;
		}





	}
}