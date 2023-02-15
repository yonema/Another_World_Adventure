#include "Fade.h"
#include "Renderers/SpriteRenderer.h"
#include "GraphicsEngine.h"
#include "../../Application.h"

namespace nsYMEngine
{
	namespace nsGraphics
	{
		CFade* CFade::m_instance = nullptr;
		const float CFade::m_kDefaultFadeTime = 1.0f;

		bool CFade::Start()
		{
			m_fadeSR = NewGO<nsRenderers::CSpriteRenderer>("FadeSpriteRenderer");

			nsSprites::SSpriteInitData initData = {};
			const auto& defaultTexture = CGraphicsEngine::GetInstance()->GetDefaultTextures();
			initData.filePath = defaultTexture.GetTextureFilePath(CDefaultTextures::enBlack);

			const float windowWidth = static_cast<float>(CApplication::GetInstance()->GetWindowWidth());
			const float windowHeight = static_cast<float>(CApplication::GetInstance()->GetWindowHeight());
			initData.spriteSize = { windowWidth, windowHeight };
			initData.alphaBlendMode = nsSprites::EnAlphaBlendMode::enTrans;
			initData.priority = nsRenderers::EnRendererPriority::enMax;
			initData.topSprite = true;

			m_fadeSR->Init(initData);
			m_fadeSR->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

			return true;
		}

		void CFade::OnDestroy()
		{
			DeleteGO(m_fadeSR);
			m_fadeSR = nullptr;

			return;
		}

		void CFade::Update(float deltaTime)
		{
			switch(m_fadeState)
			{
			case EnFadeState::enFadeOutEnd:
			case EnFadeState::enFadeInEnd:
				break;
			case EnFadeState::enFadingOut:
			case EnFadeState::enFadingIn:

				UpdateFading(deltaTime);

				break;
			}

			return;
		}

		void CFade::UpdateFading(float deltaTime) noexcept
		{
			m_fadeTime -= deltaTime;

			if (m_fadeTime <= 0.0f)
			{
				m_fadeTime = 0.0f;

				if (m_fadeState == EnFadeState::enFadingOut)
				{
					m_fadeState = EnFadeState::enFadeOutEnd;
				}
				else if (m_fadeState == EnFadeState::enFadingIn)
				{
					m_fadeState = EnFadeState::enFadeInEnd;
				}
			}

			SetFadeAlpha();

			return;
		}



		void CFade::FadeOut(float time) noexcept
		{
			if (m_fadeState == EnFadeState::enFadingOut)
			{
				// すでにフェードアウト中のため何もしない
				return;
			}

			m_fadeState = EnFadeState::enFadingOut;

			SetFadeTime(time);

			SetFadeAlpha();
		}

		void CFade::FadeIn(float time) noexcept
		{
			if (m_fadeState == EnFadeState::enFadingIn)
			{
				// すでにフェードイン中のため何もしない
				return;
			}

			m_fadeState = EnFadeState::enFadingIn;

			SetFadeTime(time);

			SetFadeAlpha();
		}

		void CFade::SetFadeAlpha() noexcept
		{
			float alpha = 1.0f;

			if (m_fadeState == EnFadeState::enFadingOut || m_fadeState == EnFadeState::enFadeOutEnd)
			{
				alpha *= 1.0f - (m_fadeTime / m_fadeInitialTime);
			}
			else
			{
				alpha *= m_fadeTime / m_fadeInitialTime;
			}

			m_fadeSR->SetMulColor({ 1.0f,1.0f,1.0f,alpha });

			return;
		}




	}
}