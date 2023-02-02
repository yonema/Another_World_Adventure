#include "YonemaEnginePreCompile.h"
#include "InnRestWindowUI.h"

#include "../../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CInnRestWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Image/Institution/Inn/Rest/Window_1.png",
            "Assets/Image/Institution/Inn/Rest/Window_2.png"
        };

        bool CInnRestWindowUI::Start()
        {
            return true;
        }

        void CInnRestWindowUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // ウィンドウ１
                    if ("" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_1, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ２
                    if ("" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CInnRestWindowUI::LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UIクラスを作成
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // ポジションをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPosition(imgData.Position);
            // ピボットをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPivot(imgData.Pivot);
        }

        void CInnRestWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CInnRestWindowUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに


        }

        void CInnRestWindowUI::Animation()
        {

        }
    }
}