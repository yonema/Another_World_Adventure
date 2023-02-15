#include "OpeningScene.h"
#include "YonejiTestScene.h"
#include "../Event/EventManager.h"
#include "../Event/EventFlow.h"
#include "../Humans/HumanModelRenderer.h"
#include "../Humans/HumanTable.h"
#include "../Event/EventController.h"
#include "../Event/EventNameTable.h"
#include "../GamePreLoading.h"
#include "../GameNowLoading.h"

namespace nsAWA
{
	namespace nsScene
	{
		bool COpeningScene::m_initialOpening = false;

		bool COpeningScene::Start()
		{
			MainCamera()->SetFarClip(5000.0f);

			m_skyCubeRenderer = NewGO<CSkyCubeRenderer>();
			m_skyCubeRenderer->Init(EnSkyType::enNormal);
			m_skyCubeRenderer->SetScale(5000.0f);
			m_skyCubeRenderer->SetAutoFollowCameraFlag(true);
			m_skyCubeRenderer->SetAutoRotateFlag(true);

			m_humanMR = NewGO<nsHumans::CHumanModelRenderer>("GoddessMR");
			m_humanMR->Init(
				"Goddess",
				CVector3::Zero(),
				CQuaternion::Identity(),
				nsHumans::g_kNameToModelFilePath.at("Goddess")
			);

			InvokeFunc([&]() {m_initialOpening = true; }, 3.0f);


			return true;
		}

		void COpeningScene::Update(float deltaTime)
		{
			auto* eventFlow = CGamePreLoading::GetInstance()->
				GetEventController()->GetEventFlow(nsEvent::GetEventNameFromTable(
						nsEvent::EnEventNameType::enGoddesAndAWTransfer));

			if (m_gameNowLoading == nullptr && (eventFlow == nullptr || eventFlow->IsClear()))
			{
				m_gameNowLoading = NewGO<CGameNowLoading>();

				InvokeFunc(
					[]()
					{
						auto* newScene = CreateScene<CYonejiTestScene>();
						newScene->Tutorial();
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

			return;
		}

		void COpeningScene::OnDestroy()
		{
			DeleteGO(m_skyCubeRenderer);
			DeleteGO(m_humanMR);
			m_gameNowLoading = nullptr;

			return;
		}


	}
}