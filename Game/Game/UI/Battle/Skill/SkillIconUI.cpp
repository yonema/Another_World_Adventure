#include "YonemaEnginePreCompile.h"
#include "SkillIconUI.h"

#include "../../../Player/PlayerManager.h"
#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CSkillIconUI::m_kLevel2DFilePath =
            "Assets/Level2D/Skill.tdl";

        const char* CSkillIconUI::m_kSkillIconFilePath =
            "Assets/Images/SkillRelated/SkillIcon.png";

        const char* CSkillIconUI::m_kFireFilePath =
            "Assets/Images/SkillRelated/Fire.png";

        bool CSkillIconUI::Start()
        {
            return true;
        }

        void CSkillIconUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う
                //スキルアイコンの土台
                    if ("SkillIcon_A" == imgData.Name)
                    {
                        // UIクラスを作成
                        LoadSkillIconSprite(EnSkillButton::enSkill_A, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    //スキルアイコンの土台
                    if ("SkillIcon_B" == imgData.Name)
                    {
                        // UIクラスを作成
                        LoadSkillIconSprite(EnSkillButton::enSkill_B, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    //スキルアイコンの土台
                    if ("SkillIcon_X" == imgData.Name)
                    {
                        // UIクラスを作成
                        LoadSkillIconSprite(EnSkillButton::enSkill_X, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    //スキルアイコンの土台
                    if ("SkillIcon_Y" == imgData.Name)
                    {
                        // UIクラスを作成
                        LoadSkillIconSprite(EnSkillButton::enSkill_Y, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    //スキルアイコンの土台
                    if ("SkillIcon_RB" == imgData.Name)
                    {
                        // UIクラスを作成
                        LoadSkillIconSprite(EnSkillButton::enSkill_RB, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }
                    //スキルアイコンの土台
                    if ("SkillIcon_RT" == imgData.Name)
                    {
                        // UIクラスを作成
                        LoadSkillIconSprite(EnSkillButton::enSkill_RT, imgData);
                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });
        }

        void CSkillIconUI::LoadSkillIconSprite(const EnSkillButton& skillNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            if ("Fire" == nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(static_cast<int>(skillNum))) {
                // UIクラスを作成
                m_spriteSkillIcon[static_cast<int>(skillNum)] = NewGO<CSpriteUI>();
                m_spriteSkillIcon[static_cast<int>(skillNum)]->LoadSprite(
                    m_kFireFilePath,
                    imgData.SpriteSize,
                    static_cast<EnRendererPriority>(imgData.Priority),
                    EnAlphaBlendMode::enTrans
                );
                m_spriteSkillIcon[static_cast<int>(skillNum)]->LoadInitData(
                    imgData.Position,
                    imgData.Scale,
                    imgData.Pivot
                );
            }
            else {
                // UIクラスを作成
                m_spriteSkillIcon[static_cast<int>(skillNum)] = NewGO<CSpriteUI>();
                m_spriteSkillIcon[static_cast<int>(skillNum)]->LoadSprite(
                    m_kSkillIconFilePath,
                    imgData.SpriteSize,
                    static_cast<EnRendererPriority>(imgData.Priority),
                    EnAlphaBlendMode::enTrans
                );
                m_spriteSkillIcon[static_cast<int>(skillNum)]->LoadInitData(
                    imgData.Position,
                    imgData.Scale,
                    imgData.Pivot
                );
            }
        }

        void CSkillIconUI::OnDestroy()
        {
            for (auto forNum : m_spriteSkillIcon) {
                DeleteGO(forNum);
            }
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