#include "YonemaEnginePreCompile.h"
#include "MenuBaseUI.h"

#include "../SpriteUI.h"
#include "Skill/MenuSkillWindowUI.h"
#include "Skill/OperationMenuSkillUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CMenuBaseUI::m_kLevel2DFilePath =
            "Assets/Level2D/MenuBase.tdl";

        const char* CMenuBaseUI::m_kSpriteMenuBaseFilePath =
            "Assets/Images/Menu/MenuBase.png";

        bool CMenuBaseUI::Start()
        {
            return true;
        }

        void CMenuBaseUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // ���j���[�̓y�䕔��
                    if ("MenuBase" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteMenuBase = NewGO<CSpriteUI>();
                        m_spriteMenuBase->LoadSprite(
                            m_kSpriteMenuBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteMenuBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });

            m_menuSkillWindowUI = NewGO<CMenuSkillWindowUI>();
            m_menuSkillWindowUI->LoadLevel();

            m_operationMenuSkillUI = NewGO<COperationMenuSkillUI>();
        }

        void CMenuBaseUI::OnDestroy()
        {
            DeleteGO(m_spriteMenuBase);

            DeleteGO(m_menuSkillWindowUI);
            DeleteGO(m_operationMenuSkillUI);
        }

        void CMenuBaseUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������


        }

        void CMenuBaseUI::Animation()
        {

        }
    }
}