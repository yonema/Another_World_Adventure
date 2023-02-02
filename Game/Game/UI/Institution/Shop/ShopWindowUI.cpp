#include "YonemaEnginePreCompile.h"
#include "ShopWindowUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CShopWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Image/Institution/Shop/Window_1.png",
            "Assets/Image/Institution/Shop/Window_2.png",
            "Assets/Image/Institution/Shop/Window_3.png",
            "Assets/Image/Institution/Shop/Window_4.png",
            "Assets/Image/Institution/Shop/Window_5.png"
        };

        bool CShopWindowUI::Start()
        {
            return true;
        }

        void CShopWindowUI::LoadLevel(const char* tdlFilePath)
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
                    // ウィンドウ３
                    if ("" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_3, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ４
                    if ("" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_4, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ５
                    if ("" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_5, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CShopWindowUI::LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UIクラスを作成
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // ポジションをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPosition(imgData.Position);
            // ピボットをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPivot(imgData.Pivot);
        }

        void CShopWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CShopWindowUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに


        }

        void CShopWindowUI::Animation()
        {

        }
    }
}