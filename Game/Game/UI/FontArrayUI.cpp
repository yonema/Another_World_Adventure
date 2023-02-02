#include "YonemaEnginePreCompile.h"
#include "FontArrayUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CFontArrayUI::Start()
        {
            return true;
        }

        void CFontArrayUI::NewLoadFont(const wchar_t* text, EnFontType fontType)
        {
            SFontParameter fontParam;
            fontParam.text = text;
            fontParam.position.x = 0.0f;
            fontParam.position.y = 0.0f;
            fontParam.pivot.x = 0.0f;
            fontParam.pivot.y = 0.0f;
            fontParam.anchor = EnAnchors::enMiddleCenter;

            m_fontRenderers.push_back(NewGO<CFontRenderer>());
            m_fontRenderers.back()->Init(fontParam, fontType);
        }

        void CFontArrayUI::OnDestroy()
        {
            for (auto forNum : m_fontRenderers) {
                DeleteGO(forNum);
            }
        }

        void CFontArrayUI::Update(float deltaTime)
        {
            // ñàÉtÉåÅ[ÉÄÇÃèàóùÇÇ±Ç±Ç…

        }
    }
}