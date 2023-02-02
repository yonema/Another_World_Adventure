#include "YonemaEnginePreCompile.h"
#include "SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CSpriteUI::Start()
        {
            return true;
        }

        void CSpriteUI::LoadSprite(
            const char* tdlFilePath,
            const CVector2& spriteSize,
            const EnGOPriority priority,
            const EnAlphaBlendMode alphaBlendMode
        )
        {
            SSpriteInitData spriteInitData;
            spriteInitData.filePath = tdlFilePath;
            spriteInitData.spriteSize = spriteSize;
            spriteInitData.alphaBlendMode = alphaBlendMode;

            // ‰æ‘œ‚Ì“Ç‚İ‚İ
            m_spriteRenderer = NewGO<CSpriteRenderer>(priority);
            m_spriteRenderer->Init(spriteInitData);
        }

        void CSpriteUI::OnDestroy()
        {
            DeleteGO(m_spriteRenderer);
        }

        void CSpriteUI::Update(float deltaTime)
        {
            // –ˆƒtƒŒ[ƒ€‚Ìˆ—‚ğ‚±‚±‚É

        }
    }
}