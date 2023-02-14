#include "GameNowLoading.h"
#include "../Application.h"
namespace nsAWA
{
	bool CGameNowLoading::Start()
	{
		SSpriteInitData spriteInitData = {};
		spriteInitData.filePath = "Assets/Images/Presets/black.jpg";
		const float windowWidth = static_cast<float>(CApplication::GetInstance()->GetWindowWidth());
		const float windowHeight = static_cast<float>(CApplication::GetInstance()->GetWindowHeight());
		spriteInitData.spriteSize = { windowWidth, windowHeight };

		m_spriteRenderer = NewGO<CSpriteRenderer>("NowLoadingSprite");
		m_spriteRenderer->Init(spriteInitData);

		SFontParameter fontParam = {};
		fontParam.text = L"NowLoading...";
		fontParam.color = CVector4::White();
		m_fontRenderer = NewGO<CFontRenderer>("NowLoadingFont");
		m_fontRenderer->Init(fontParam);

		return true;;
	}

	void CGameNowLoading::Update(float deltaTime)
	{
		m_degAngle += 5.0f * deltaTime;
		if (m_degAngle >= 360.0f)
		{
			m_degAngle -= 360.0f;
		}
		m_fontRenderer->SetRotation(m_degAngle);


		if (m_exitFunc())
		{
			DeleteGO(this);
		}

		return;
	}

	void CGameNowLoading::OnDestroy()
	{
		DeleteGO(m_spriteRenderer);
		DeleteGO(m_fontRenderer);

		return;
	}
}