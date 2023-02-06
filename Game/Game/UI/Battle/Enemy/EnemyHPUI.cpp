#include "YonemaEnginePreCompile.h"
#include "EnemyHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyHPUI::m_kLevel2DFilePath =
            "Assets/Level2D/EnemyHPBar.tdl";

        const char* CEnemyHPUI::m_kSpriteHPBarFilePath = 
            "Assets/Images/FitnessBar/Common/Bar_HP.png";
        const char* CEnemyHPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CEnemyHPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";
        const char* CEnemyHPUI::m_kSpriteDangerFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_Danger.png";
        const char* CEnemyHPUI::m_kSpriteDecreaaseFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_DecreaseAnimation.png";

        const float CEnemyHPUI::m_kMaxBarWidthSize = 0.3f;

        bool CEnemyHPUI::Start()
        {
            return true;
        }

        void CEnemyHPUI::LoadLevel(const CVector2& basePosition)
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �G��HP�o�[
                    if ("Bar_HP" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(
                            m_kSpriteHPBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteHPBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountHPBar = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̘g
                    else if ("BarFrame" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(
                            m_kSpriteFrameFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteFrame->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountFrame = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̉��n
                    else if ("BarGroundwork" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(
                            m_kSpriteBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBase = basePosition - imgData.Position;
                        
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̃s���`���̂��
                    else if ("Bar_HP_Danger" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite(
                            m_kSpriteDangerFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteDanger->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );
                        // ��\���ɂ���
                        m_spriteDanger->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountDanger = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // HP�o�[�̃f�B���C�A�j���[�V�����p��UI
                    else if ("HP_DecreaseAnimationBar" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteDecrease = NewGO<CSpriteUI>();
                        m_spriteDecrease->LoadSprite(
                            m_kSpriteDecreaaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteDecrease->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );
                        //m_spriteDecrease->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountDanger = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });
        }

        void CEnemyHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
        }

        void CEnemyHPUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // HP�o�[�̃A�j���[�V����
            Animation();

        }

        void CEnemyHPUI::Animation()
        {
            // �Q�[�W�̒����i�����j��K�p
            m_spriteHPBar->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
        }

        void CEnemyHPUI::SetUIPosition(const CVector2& position)
        {
            m_spriteHPBar->SetPosition(position + m_correctionAmountHPBar);
            m_spriteFrame->SetPosition(position + m_correctionAmountFrame);
            m_spriteBase->SetPosition(position + m_correctionAmountBase);
            m_spriteDanger->SetPosition(position + m_correctionAmountDanger);
        }
    }
}