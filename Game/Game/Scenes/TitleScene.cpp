#include "TitleScene.h"
#include "MainGameScene.h"
#include "OpeningScene.h"
#include "YonejiTestScene.h"
#include "EnterGameScene.h"


namespace nsAWA
{
	namespace nsScene
	{
		bool CTitleScene::Start()
		{
			{
				m_titleBackSR = NewGO<CSpriteRenderer>("TitleBackSR");
				SSpriteInitData initData = {};
				initData.filePath = "Assets/Images/Title/TitleBack.png";
				initData.spriteSize = { 1280.0f, 720.0f };
				m_titleBackSR->Init(initData);
			}

			{
				m_titleLogoSR = NewGO<CSpriteRenderer>("TitleLogoSR");
				SSpriteInitData initData = {};
				initData.filePath = "Assets/Images/Title/TitleLogo.png";
				initData.spriteSize = { 775.0f, 256.0f };
				initData.alphaBlendMode = EnAlphaBlendMode::enTrans;
				m_titleLogoSR->Init(initData);
				m_titleLogoSR->SetPosition({ 0.0f,-150.0f });
			}

			m_fontRenderer = NewGO<CFontRenderer>();
			SFontParameter param(L"Press A Button");
			m_fontRenderer->Init(param);
			m_fontRenderer->SetPosition({ 0.0f, 200.0f });

			return true;
		}

		void CTitleScene::Update(float deltaTime)
		{
			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				CreateSceneWithFade<CEnterGameScene>();
			}
			else if (Keyboard()->IsTrigger(EnKeyButton::en0))
			{
				CreateSceneWithFade<COpeningScene>();
			}
			else if (Keyboard()->IsTrigger(EnKeyButton::en1))
			{
				CreateSceneWithFade<CYonejiTestScene>();
			}
			else if (Keyboard()->IsTrigger(EnKeyButton::en2))
			{
				CreateSceneWithFade<CMainGameScene>();
			}
			else if (Keyboard()->IsTrigger(EnKeyButton::enEscape))
			{
				ExitGame();
			}

			return;
		}

		void CTitleScene::OnDestroy()
		{
			DeleteGO(m_fontRenderer);
			DeleteGO(m_titleLogoSR);
			DeleteGO(m_titleBackSR);

			return;
		}



	}
}