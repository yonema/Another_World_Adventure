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

        // �s���`���胉�C��
        const float CPlayerHPUI::m_kDangerLine = 0.3f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTime = 5.0f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTimeAmount = 0.1f;
        // �����A�j���[�V�����̌�����
        const float CPlayerHPUI::m_kDecreaseBarDecreaseAmount = 0.005f;

        const float CPlayerHPUI::m_kMaxBarWidthSize = 0.5f;

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
                            static_cast<EnGOPriority>(imgData.Priority),
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
                    if ("HP_BarFrame" == imgData.Name)
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
                    // �v���C���[��HP�o�[�̉��n
                    if ("HP_BarGroundwork" == imgData.Name)
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
                    // �v���C���[��HP�o�[�̃s���`���̂��
                    if ("HP_DangerBar" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        //m_spriteDanger = NewGO<CSpriteUI>();
                        //m_spriteDanger->LoadSprite(
                        //    m_kSpriteDangerFilePath,
                        //    imgData.SpriteSize,
                        //    static_cast<EnGOPriority>(imgData.Priority),
                        //    EnAlphaBlendMode::enTrans
                        //);
                        //m_spriteDanger->LoadInitData(
                        //    imgData.Position,
                        //    imgData.Scale,
                        //    imgData.Pivot
                        //);

                        //// ��\���ɂ���
                        //m_spriteDanger->Deactivate();
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // HP�o�[�̃f�B���C�A�j���[�V�����p��UI
                    if ("HP_DecreaseAnimationBar" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteDecrease = NewGO<CSpriteUI>();
                        m_spriteDecrease->LoadSprite(
                            m_kSpriteDecreaaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnGOPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteDecrease->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        //m_spriteDecrease->Deactivate();

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CPlayerHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
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
            //if (m_kDangerLine > m_barWidthSize) {
            //    ChangeDangerUI(true);
            //}
            //else {
            //    ChangeDangerUI(false);
            //}

            // �Q�[�W�̒����i�����j��K�pm_decreaseBarWidthSize
            m_spriteHPBar->SetScale({ m_decreaseBarWidthSize,0.5f,1.0f });
            //m_spriteDanger->SetScale({ m_barWidthSize,0.5f,1.0f });
            m_spriteDecrease->SetScale({ m_barWidthSize,0.5f,1.0f });

            m_oldDecreaseBarWidthSize = m_decreaseBarWidthSize;
        }

        void CPlayerHPUI::ChangeDangerUI(const bool flagDanger)
        {
            // �s���`��Ԃ̂Ƃ�
            if (true == flagDanger) {
                // �s���`��Ԃ�UI����\���Ȃ�
                if (false == m_spriteDanger->IsActive()) {
                    m_spriteDanger->Activate();
                    m_spriteHPBar->Deactivate();
                }
            }
            // �s���`��Ԃł͂Ȃ��Ƃ�
            else {
                // �s���`��Ԃ�UI���\����ԂȂ�
                if (true == m_spriteDanger->IsActive()) {
                    m_spriteDanger->Deactivate();
                    m_spriteHPBar->Activate();
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
            // �Â���񂪃��A���^�C���̂�菭�Ȃ��ꍇ
            if (m_decreaseBarWidthSize <= m_barWidthSize) {
                m_decreaseBarWidthSize = m_barWidthSize;
                return;
            }

            // �A�j���[�V�������n�߂�܂ł̃^�C�}�[
            if (false == StartDecreaseBarAnimationTimer()) {
                return;
            }

            // �Â��o�[�����A���^�C���̃o�[�ɏ��X�ɋ߂Â��A�j���[�V����
            // ���A�j���[�V�������x�͑��߂ŁI
            m_decreaseBarWidthSize -= m_kDecreaseBarDecreaseAmount;
        }
    }
}