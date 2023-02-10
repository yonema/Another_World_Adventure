#include "OpeningScene.h"
#include "TitleScene.h"

namespace nsAWA
{
	namespace nsScene
	{
		bool COpeningScene::Start()
		{
			m_fontRenderer = NewGO<CFontRenderer>();

			SFontParameter param(L"�I�[�v�j���O�V�[��\nA�{�^���������Ă�������");
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