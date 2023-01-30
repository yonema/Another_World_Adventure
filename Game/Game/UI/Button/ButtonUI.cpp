#include "YonemaEnginePreCompile.h"
#include "ButtonUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CButtonUI::m_kSpriteButtonFilePath[EnButtonUI::enMaxButtonUI] =
        {
            "Assets/Image/ButtonRelated/Button_A.png",
            "Assets/Image/ButtonRelated/Button_B.png",
            "Assets/Image/ButtonRelated/Button_X.png",
            "Assets/Image/ButtonRelated/Button_Y.png",
            "Assets/Image/ButtonRelated/Button_L.png",
            "Assets/Image/ButtonRelated/Button_R.png",
            "Assets/Image/ButtonRelated/Trigger_L.png",
            "Assets/Image/ButtonRelated/Trigger_R.png",
        };

        bool CButtonUI::Start()
        {
            return true;
        }

        void CButtonUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // Aボタン
                    if (imgData.EqualObjectName(L"Aボタン") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enA, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Bボタン
                    if (imgData.EqualObjectName(L"Bボタン") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enB, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Xボタン
                    if (imgData.EqualObjectName(L"Xボタン") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enX, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Yボタン
                    if (imgData.EqualObjectName(L"Yボタン") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enY, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Lボタン
                    if (imgData.EqualObjectName(L"Lボタン") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enBL, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Rボタン
                    if (imgData.EqualObjectName(L"Rボタン") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enBR, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Lトリガー
                    if (imgData.EqualObjectName(L"Lトリガー") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enTL, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // Rトリガー
                    if (imgData.EqualObjectName(L"Rトリガー") == true)
                    {
                        // 対応したボタンのUIを読み込む
                        LoadButtonSprite(EnButtonUI::enTR, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CButtonUI::LoadButtonSprite(const int buttonUINum, LevelObjectData& imgData)
        {
            // UIクラスを作成
            m_spriteButton = NewGO<CSpriteUI>();
            m_spriteButton->LoadSprite(m_kSpriteButtonFilePath[buttonUINum]);
            // ポジションをロードした画像と同じにする
            m_spriteButton->SetPosition(imgData.position);
            // ピボットをロードした画像と同じにする
            m_spriteButton->SetPivot(imgData.pivot);
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