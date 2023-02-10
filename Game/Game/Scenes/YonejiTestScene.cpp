#include "YonejiTestScene.h"
#include "TitleScene.h"
#include "../Humans/HumanManager.h"
#include "../LoadGame.h"

// ÇªÇÃÇ§Çøè¡Ç∑ó\íË

namespace nsAWA
{
	namespace nsScene
	{
		bool CYonejiTestScene::Start()
		{

			m_humanManager = NewGO <nsHumans::CHumanManager>("HumanManager");
			m_humanManager->GenerateBase(true);

			constexpr float kFarClip = 5000.0f;
			MainCamera()->SetFarClip(kFarClip);

			m_nowLoadingFR = NewGO<CFontRenderer>();
			SFontParameter param(L"NowLoading!");
			m_nowLoadingFR->Init(param);

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
			m_humanManager->Release();

			DeleteGO(m_loadGame);
			m_loadGame = nullptr;

			DeleteGO(m_nowLoadingFR);
			m_nowLoadingFR = nullptr;

			return;
		}

		void CYonejiTestScene::InitAfterBaseLoaded(float deltaTime)
		{
			if (m_isLevelLoaded)
			{
				return;
			}

			if (m_humanManager->IsBaseLoaded() != true)
			{
				static float rotate = 0.0f;
				rotate += 2.0f * deltaTime;

				if (m_nowLoadingFR)
				{
					m_nowLoadingFR->SetRotation(rotate);
				}

				return;
			}

			DeleteGO(m_nowLoadingFR);
			m_nowLoadingFR = nullptr;

			m_loadGame = NewGO<CLoadGame>();

			SLevel3DInitData initData;
			initData.isCreateStaticPhysicsObjectForAll = false;

			m_level3D.Init(
				"Assets/Level3D/WorldLevel.fbx",
				initData,
				[&](const SLevelChipData& chipData)->bool
				{
					if (chipData.ForwardMatchName("Humans_"))
					{
						m_humanManager->GenerateHuman(
							chipData.name, chipData.position, chipData.rotation);
						return true;
					}

					return true;
				}
			);


			m_isLevelLoaded = true;

			return;
		}




	}
}