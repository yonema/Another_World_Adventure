#include "YonemaEnginePreCompile.h"
#include "ButtonUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CButtonUI::m_kSpriteButtonFilePath[EnButtonUI::enMaxButtonUI] =
        {
            "Assets/Images/ButtonRelated/Button_A.png",
            "Assets/Images/ButtonRelated/Button_B.png",
            "Assets/Images/ButtonRelated/Button_X.png",
            "Assets/Images/ButtonRelated/Button_Y.png",
            "Assets/Images/ButtonRelated/Button_L.png",
            "Assets/Images/ButtonRelated/Button_R.png",
            "Assets/Images/ButtonRelated/Trigger_L.png",
            "Assets/Images/ButtonRelated/Trigger_R.png",
        };

        bool CButtonUI::Start()
        {
            return true;
        }

        void CButtonUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // Aボタン
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enA, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Bボタン
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enB, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Xボタン
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enX, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Yボタン
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enY, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Lボタン
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enBL, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Rボタン
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enBR, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Lトリガー
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enTL, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Rトリガー
                    if ("" == imgData.Name)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enTR, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CButtonUI::LoadButtonSprite(const int buttonUINum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UIクラスを作成
            m_spriteButton = NewGO<CSpriteUI>();
            m_spriteButton->LoadSprite(m_kSpriteButtonFilePath[buttonUINum]);
            // ポジションをロードした画像と同じにする
            m_spriteButton->SetPosition(imgData.Position);
            // ピボットをロードした画像と同じにする
            m_spriteButton->SetPivot(imgData.Pivot);
        }

        void CButtonUI::OnDestroy()
        {
            DeleteGO(m_spriteButton);
        }

        void CButtonUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // MPバーのアニメーション
            Animation();

        }

        void CButtonUI::Animation()
        {

        }
    }
}