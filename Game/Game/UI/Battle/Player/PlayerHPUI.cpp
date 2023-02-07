#include "YonemaEnginePreCompile.h"
#include "PlayerHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerHPUI::m_kLevel2DFilePath =
            "Assets/Level2D/HP_Bar.tdl";

        const char* CPlayerHPUI::m_kSpriteHPBarFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP.png";
        const char* CPlayerHPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CPlayerHPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";
        const char* CPlayerHPUI::m_kSpriteDangerFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_Danger.png";
        const char* CPlayerHPUI::m_kSpriteDecreaaseFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_DecreaseAnimation.png";

        const float CPlayerHPUI::m_kMaxBarWidthSize = 0.5f;
        const float CPlayerHPUI::m_kDangerLine = 0.3f * m_kMaxBarWidthSize;

        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTime = 5.0f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTimeAmount = 0.1f;
        const float CPlayerHPUI::m_kDecreaseBarDecreaseAmount = 0.005f;



        bool CPlayerHPUI::Start()
        {
            return true;
        }

        void CPlayerHPUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �v���C���[��HP�o�[
                    if ("HP_Bar" == imgData.Name)
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

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̘g
                    else if ("HP_BarFrame" == imgData.Name)
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

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̉��n
                    else if ("HP_BarGroundwork" == imgData.Name)
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

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̃s���`���̂��
                    else if ("HP_DangerBar" == imgData.Name)
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
                        m_spriteDanger->SetDrawingFlag(false);
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

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });
        }

        void CPlayerHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
            DeleteGO(m_spriteDecrease);
        }

        void CPlayerHPUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // HP�o�[�̃A�j���[�V����
            Animation();

        }

        void CPlayerHPUI::Animation()
        {
            // �x��Č�������Q�[�W�̃A�j���[�V����
            DecreaseBarAnimation();

            // HP���R����؂��Ă��邩���m�F
            ChangeDangerUI();


            // �Q�[�W�̒����i�����j��K�p
            m_spriteHPBar->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
            m_spriteDanger->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
            m_spriteDecrease->SetScale({ m_decreaseBarWidthSize,m_kMaxBarWidthSize,1.0f });

            // ���݂̃o�[�̏���ۑ�
            m_oldBarWidthSize = m_barWidthSize;
        }

        void CPlayerHPUI::ChangeDangerUI()
        {
            // �s���`��Ԃ̂Ƃ�
            if (m_kDangerLine > m_barWidthSize) {
                // �s���`��Ԃ�UI����\���Ȃ�
                if (false == m_spriteDanger->IsDrawingFlag()) {
                    m_spriteDanger->SetDrawingFlag(true);
                    m_spriteHPBar->SetDrawingFlag(false);
                }
            }
            // �s���`��Ԃł͂Ȃ��Ƃ�
            else {
                // �s���`��Ԃ�UI���\����ԂȂ�
                if (true == m_spriteDanger->IsDrawingFlag()) {
                    m_spriteDanger->SetDrawingFlag(false);
                    m_spriteHPBar->SetDrawingFlag(true);
                }
            }
        }

        const bool CPlayerHPUI::StartDecreaseBarAnimationTimer()
        {
            // �^�C�}�[���ݒ莞�Ԃ𒴂�����
            if (m_kStartDecreaseBarAnimationTime <= m_startDecreaseBarAnimationTimer) {
                return true;
            }

            // �^�C�}�[��i�߂�
            m_startDecreaseBarAnimationTimer += m_kStartDecreaseBarAnimationTimeAmount;

            return false;
        }

        void CPlayerHPUI::DecreaseBarAnimation()
        {
            // �A�j���[�V�����o�[��HP�o�[���Z���ꍇ
            if (m_decreaseBarWidthSize <= m_barWidthSize) {
                m_decreaseBarWidthSize = m_barWidthSize;
                return;
            }

            // �A�j���[�V�������n�߂�܂ł̃^�C�}�[
            if (false == StartDecreaseBarAnimationTimer()) {
                return;
            }

            // �Â��o�[�����A���^�C���̃o�[�ɏ��X�ɋ߂Â��A�j���[�V����
            m_decreaseBarWidthSize -= m_kDecreaseBarDecreaseAmount;
        }
    }
}