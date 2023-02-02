#include "YonemaEnginePreCompile.h"
#include "PlayerMPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerMPUI::m_kLevel2DFilePath =
            "Assets/Level2D/MP_Bar.tdl";

        const char* CPlayerMPUI::m_kSpriteMPBarFilePath = 
            "Assets/Images/FitnessBar/Player/Bar_MP.png";
        const char* CPlayerMPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CPlayerMPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";

        bool CPlayerMPUI::Start()
        {
            return true;
        }

        void CPlayerMPUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // MP�o�[
                    if ("MP_Bar" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite(
                            m_kSpriteMPBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnGOPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteMPBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��MP�o�[�̘g
                    if ("MP_BarFrame" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(
                            m_kSpriteFrameFilePath,
                            imgData.SpriteSize,
                            static_cast<EnGOPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteFrame->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��MP�o�[�̉��n
                    if ("MP_BarGroundwork" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(
                            m_kSpriteBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnGOPriority>(imgData.Priority),
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
                });
        }

        void CPlayerMPUI::OnDestroy()
        {
            DeleteGO(m_spriteMPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
        }

        void CPlayerMPUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // MP�o�[�̃A�j���[�V����
            Animation();

        }

        void CPlayerMPUI::Animation()
        {
            // �Q�[�W�̒����i�����j��K�p
            //m_spriteMPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}