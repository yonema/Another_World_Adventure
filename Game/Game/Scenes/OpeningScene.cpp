#include "OpeningScene.h"
#include "TitleScene.h"

namespace nsAWA
{
	namespace nsScene
	{
		bool COpeningScene::Start()
		{
			m_fontRenderer = NewGO<CFontRenderer>();

			SFontParameter param(L"オープニングシーン\nAボタンを押してください");
			m_fontRenderer->Init(param);

			return true;
		}

		void COpeningScene::Update(float deltaTime)
		{
			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				CreateScene<CTitleScene>();
			}

			return;
		}

		void COpeningScene::OnDestroy()
		{
			DeleteGO(m_fontRenderer);

			return;
		}


	}
}