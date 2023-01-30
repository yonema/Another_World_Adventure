#include "YonemaEnginePreCompile.h"
#include "ConversationWindowUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CConversationWindowUI::m_kSpriteWindowFilePath =
            "ファイルパス";

        bool CConversationWindowUI::Start()
        {
            return true;
        }

        void CConversationWindowUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // ウィンドウ１
                    if (imgData.EqualObjectName(L"ウィンドウ１") == true)
                    {
                        // UIクラスを作成
                        m_spriteWindow = NewGO<CSpriteUI>();
                        m_spriteWindow->LoadSprite(m_kSpriteWindowFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteWindow->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteWindow->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CConversationWindowUI::OnDestroy()
        {
            DeleteGO(m_spriteWindow);
        }

        void CConversationWindowUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに


        }

        void CConversationWindowUI::Animation()
        {

        }
    }
}