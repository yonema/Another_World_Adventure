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
                { // ���[�h���郌�x�����ɃN�G�����s��
                //�X�L���A�C�R���̓y��
                    if ("SkillIcon_A" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        LoadSkillIconSprite(EnSkillButton::enSkill_A, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    //�X�L���A�C�R���̓y��
                    if ("SkillIcon_B" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        LoadSkillIconSprite(EnSkillButton::enSkill_B, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    //�X�L���A�C�R���̓y��
                    if ("SkillIcon_X" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        LoadSkillIconSprite(EnSkillButton::enSkill_X, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    //�X�L���A�C�R���̓y��
                    if ("SkillIcon_Y" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        LoadSkillIconSprite(EnSkillButton::enSkill_Y, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    //�X�L���A�C�R���̓y��
                    if ("SkillIcon_RB" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        LoadSkillIconSprite(EnSkillButton::enSkill_RB, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    //�X�L���A�C�R���̓y��
                    if ("SkillIcon_RT" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        LoadSkillIconSprite(EnSkillButton::enSkill_RT, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });
        }

        void CSkillIconUI::LoadSkillIconSprite(const EnSkillButton& skillNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            if ("Fire" == nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(static_cast<int>(skillNum))) {
                // UI�N���X���쐬
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
                // UI�N���X���쐬
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
            // ���t���[���̏�����������

        }

        void CSkillIconUI::Animation()
        {

        }
    }
}