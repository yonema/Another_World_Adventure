#include "YonemaEnginePreCompile.h"
#include "MenuStatusWindowUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CMenuStatusWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Images/Menu/Status/Window_1.png",
            "Assets/Images/Menu/Status/Window_2.png"
        };

        bool CMenuStatusWindowUI::Start()
        {
            return true;
        }

        void CMenuStatusWindowUI::LoadLevel(const char* tdlFilePath)
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
                    else if ("" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });
        }

        void CMenuStatusWindowUI::LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UIクラスを作成
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // ポジションをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPosition(imgData.Position);
            // ピボットをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPivot(imgData.Pivot);
        }

        void CMenuStatusWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CMenuStatusWindowUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに


        }

        void CMenuStatusWindowUI::Animation()
        {

        }
    }
}