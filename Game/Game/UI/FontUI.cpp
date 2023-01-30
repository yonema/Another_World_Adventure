#include "YonemaEnginePreCompile.h"
#include "FontUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CFontUI::Start()
        {
            return true;
        }

        void CFontUI::LoadFont(const wchar_t* text, EnFontType fontType)
        {
            if (nullptr == m_fontRenderer) {
                return;
            }
            
            SFontParameter fontParam;
            fontParam.text = text;
            fontParam.position.x = 0.0f;
            fontParam.position.y = 0.0f;
            fontParam.pivot.x = 0.0f;
            fontParam.pivot.y = 0.0f;
            fontParam.anchor = EnAnchors::enMiddleCenter;

            m_fontRenderer = NewGO<CFontRenderer>();
            m_fontRenderer->Init(fontParam, fontType);
        }

        void CFontUI::OnDestroy()
        {
            DeleteGO(m_fontRenderer);
        }

        void CFontUI::Update(float deltaTime)
        {
            // ñàÉtÉåÅ[ÉÄÇÃèàóùÇÇ±Ç±Ç…

        }
    }
}