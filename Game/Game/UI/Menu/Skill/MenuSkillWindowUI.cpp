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
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �E�B���h�E�P
                    if ("Window_1" == imgData.Name)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_1, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�Q
                    else if ("Window_2" == imgData.Name)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�R
                    else if ("Window_3" == imgData.Name)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_3, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�S
                    else if ("Window_4" == imgData.Name)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_4, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });
        }

        void CMenuSkillWindowUI::LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UI�N���X���쐬
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
            // ���t���[���̏�����������


        }

        void CMenuSkillWindowUI::Animation()
        {

        }
    }
}