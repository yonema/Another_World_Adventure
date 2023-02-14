#include "GameNowLoading.h"
#include "../Application.h"
namespace nsAWA
{
	const float CGameNowLoading::m_kIconAnimSwitchTime = 0.15f;


	bool CGameNowLoading::Start()
	{
		Fade()->FadeIn(0.2f);

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
		fontParam.anchor = EnAnchors::enBottonRight;
		fontParam.pivot = { 1.0f,1.0f };
		fontParam.position = { -50.0f,-20.0f };
		m_fontRenderer = NewGO<CFontRenderer>("NowLoadingFont");
		m_fontRenderer->Init(fontParam);

		int idx = 0;
		for (auto& iconSR : m_iconAnimSRArray)
		{
			SSpriteInitData iconInitData;
			std::string filePath = "Assets/Images/Loading/Giyara_Icon_";
			filePath += std::to_string(idx + 1);
			filePath += ".png";
			iconInitData.filePath = filePath.c_str();
			iconInitData.spriteSize = { 256.0f * 0.5f, 256.0f * 0.5f };
			iconInitData.alphaBlendMode = EnAlphaBlendMode::enTrans;
			iconSR = NewGO<CSpriteRenderer>();
			iconSR->SetAnchor(EnAnchors::enBottonRight);
			iconSR->SetPivot({ 1.0f,1.0f });
			iconSR->SetPosition({ -50.0f, -50.0f });
			iconSR->Init(iconInitData);

			idx++;
		}

		return true;;
	}

	void CGameNowLoading::Update(float deltaTime)
	{
		m_timer += deltaTime;

		if (m_timer >= m_kIconAnimSwitchTime)
		{
			m_timer = 0.0f;
			m_iconAnimIdx++;
		}

		if (m_iconAnimIdx >= m_kNumIconAnims)
		{
			m_iconAnimIdx = 0;
		}

		int idx = 0;
		for (auto& iconSR : m_iconAnimSRArray)
		{
			if (idx == m_iconAnimIdx)
			{
				iconSR->SetDrawingFlag(true);
			}
			else
			{
				iconSR->SetDrawingFlag(false);
			}
			idx++;
		}


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
		for (auto& iconSR : m_iconAnimSRArray)
		{
			DeleteGO(iconSR);
			iconSR = nullptr;
		}	

		if (m_enableFadeInOnDestroy)
		{
			Fade()->FadeIn();
		}

		return;
	}
}