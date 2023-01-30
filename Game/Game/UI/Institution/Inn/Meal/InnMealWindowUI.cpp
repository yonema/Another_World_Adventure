#include "YonemaEnginePreCompile.h"
#include "InnMealWindowUI.h"

#include "../../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CInnMealWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Image/Institution/Inn/Meal/Window_1.png",
            "Assets/Image/Institution/Inn/Meal/Window_2.png",
            "Assets/Image/Institution/Inn/Meal/Window_3.png"
        };

        bool CInnMealWindowUI::Start()
        {
            return true;
        }

        void CInnMealWindowUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // ウィンドウ１
                    if (imgData.EqualObjectName(L"ウィンドウ１") == true)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_1, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ２
                    if (imgData.EqualObjectName(L"ウィンドウ２") == true)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ３
                    if (imgData.EqualObjectName(L"ウィンドウ３") == true)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_3, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CInnMealWindowUI::LoadWindowSprite(const int windowNum, LevelObjectData& imgData)
        {
            // UIクラスを作成
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // ポジションをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPosition(imgData.position);
            // ピボットをロードした画像と同じにする
            m_spriteWindow[windowNum]->SetPivot(imgData.pivot);
        }

        void CInnMealWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CInnMealWindowUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに


        }

        void CInnMealWindowUI::Animation()
        {

        }
    }
}