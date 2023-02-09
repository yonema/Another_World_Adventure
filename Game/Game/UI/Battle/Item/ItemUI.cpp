#include "YonemaEnginePreCompile.h"
#include "ItemUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CItemUI::m_kLevel2DFilePath =
            "Assets/Level2D/Item.tdl";

        const char* CItemUI::m_kItemBaseSpriteFilePath =
            "Assets/Images/ItemRelated/ItemBase.png";

        bool CItemUI::Start()
        {
            return true;
        }

        void CItemUI::LoadLevel()
        {
            
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �A�C�e���I��UI�̓y�䕔��
                    if ("ItemBase" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(
                            m_kItemBaseSpriteFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̘g
                    //else if ("" == imgData.Name)
                    //{
                    //    // UI�N���X���쐬
                    //    m_spriteItemIcon = NewGO<CSpriteUI>();
                    //    m_spriteItemIcon->LoadSprite(
                    //        "�t�@�C���p�X",
                    //        imgData.SpriteSize,
                    //        static_cast<EnRendererPriority>(imgData.Priority),
                    //        EnAlphaBlendMode::enTrans
                    //    );
                    //    m_spriteItemIcon->LoadInitData(
                    //        imgData.Position,
                    //        imgData.Scale,
                    //        imgData.Pivot
                    //    );

                    //    // �t�b�N�����̂ŁAtrue��Ԃ�
                    //    return true;
                    //}

                    return false;
                });
        }

        void CItemUI::OnDestroy()
        {

        }

        void CItemUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            
            Animation();

        }

        void CItemUI::Animation()
        {

        }

        void CItemUI::ActiveDrawing()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteBase->SetDrawingFlag(true);
            //m_spriteItemIcon->SetDrawingFlag(true);
        }

        void CItemUI::DeactiveDrawing()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteBase->SetDrawingFlag(false);
            //m_spriteItemIcon->SetDrawingFlag(false);
        }
    }
}