#include "YonemaEnginePreCompile.h"
#include "SkillIconUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CSkillIconUI::Start()
        {
            return true;
        }

        void CSkillIconUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う
                //スキルアイコンの土台
                    if (imgData.EqualObjectName(L"スキルアイコンの土台") == true)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteBase->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBase->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // スキルアイコンのイラスト
                    if (imgData.EqualObjectName(L"スキルアイコンのイラスト") == true)
                    {
                        // UIクラスを作成
                        m_spriteSkill = NewGO<CSpriteUI>();
                        m_spriteSkill->LoadSprite("ファイルパス");
                        // ポジションをロードした画像と同じにする
                        m_spriteSkill->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteSkill->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CSkillIconUI::OnDestroy()
        {
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteSkill);
        }

        void CSkillIconUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

        }

        void CSkillIconUI::Animation()
        {

        }
    }
}