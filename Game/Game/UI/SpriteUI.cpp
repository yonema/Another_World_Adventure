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

        void CSpriteUI::LoadSprite(const char* tdlFilePath)
        {
            SSpriteInitData spriteInitData;
            spriteInitData.filePath = tdlFilePath;
            // スプライトサイズは仮
            spriteInitData.spriteSize = { 100.0f,100.0f };
            // 画像の読み込み
            m_spriteRenderer = NewGO<CSpriteRenderer>();
            m_spriteRenderer->Init(spriteInitData);
        }

        void CSpriteUI::OnDestroy()
        {
            DeleteGO(m_spriteRenderer);
        }

        void CSpriteUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

        }
    }
}