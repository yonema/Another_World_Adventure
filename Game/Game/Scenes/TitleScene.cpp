#include "TitleScene.h"
#include "MainGameScene.h"
#include "OpeningScene.h"
#include "YonejiTestScene.h"

namespace nsAWA
{
	namespace nsScene
	{
		bool CTitleScene::Start()
		{
			m_fontRenderer = NewGO<CFontRenderer>();

			SFontParameter param(L"タイトルシーン\nAボタンを押してください");
			m_fontRenderer->Init(param);

			return true;
		}

		void CTitleScene::Update(float deltaTime)
		{
			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				CreateScene<CMainGameScene>();
			}
			else if (Keyboard()->IsTrigger(EnKeyButton::en0))
			{
				CreateScene<COpeningScene>();
			}
			else if (Keyboard()->IsTrigger(EnKeyButton::en1))
			{
				CreateScene<CYonejiTestScene>();
			}

			return;
		}

		void CTitleScene::OnDestroy()
		{
			DeleteGO(m_fontRenderer);

			return;
		}



	}
}