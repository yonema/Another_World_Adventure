#include "YonemaEnginePreCompile.h"
#include "MenuSkillWindowUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CMenuSkillWindowUI::m_kLevel2DFilePath =
            "Assets/Level2D/Menu_Skill.tdl";

        const char* CMenuSkillWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Images/Menu/Skill/Window_1.png",
            "Assets/Images/Menu/Skill/Window_2.png",
            "Assets/Images/Menu/Skill/Window_3.png",
            "Assets/Images/Menu/Skill/Window_4.png"
        };

        bool CMenuSkillWindowUI::Start()
        {
            SetFlagUpdateTable(EnMenuUpdateFlagTable::enMenu);

            return true;
        }

        void CMenuSkillWindowUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // ウィンドウ１
                    if ("Window_1" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_1, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ２
                    else if ("Window_2" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ３
                    else if ("Window_3" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_3, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // ウィンドウ４
                    else if ("Window_4" == imgData.Name)
                    {
                        // 対応したウィンドウのUIを読み込む
                        LoadWindowSprite(EnWindowNumber::enWindow_4, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });
        }

        void CMenuSkillWindowUI::LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UIクラスを作成
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(
                m_kSpriteWindowFilePath[windowNum],
                imgData.SpriteSize,
                static_cast<EnRendererPriority>(imgData.Priority),
                EnAlphaBlendMode::enTrans
            );
            m_spriteWindow[windowNum]->LoadInitData(
                imgData.Position,
                imgData.Scale,
                imgData.Pivot
            );
            m_spriteWindow[windowNum]->SetMenuUpdate();
        }

        void CMenuSkillWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CMenuSkillWindowUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに


        }

        void CMenuSkillWindowUI::Animation()
        {

        }
    }
}