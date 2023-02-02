#include "YonemaEnginePreCompile.h"
#include "PlayerHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerHPUI::m_kSpriteHPBarFilePath =
            "Assets/Image/FitnessBar/Common/Bar_HP.png";
        const char* CPlayerHPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CPlayerHPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";
        const char* CPlayerHPUI::m_kSpriteDangerFilePath =
            "Assets/Image/FitnessBar/Common/Bar_HP_Danger.png";
        const char* CPlayerHPUI::m_kSpriteDecreaaseFilePath =
            "�t�@�C���p�X";

        // �s���`���胉�C��
        const float CPlayerHPUI::m_kDangerLine = 0.3f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTime = 1.0f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTimeAmount = 0.1f;
        // �����A�j���[�V�����̌�����
        const float CPlayerHPUI::m_kDecreaseBarDecreaseAmount = 0.01f;

        bool CPlayerHPUI::Start()
        {
            return true;
        }

        void CPlayerHPUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �v���C���[��HP�o�[
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteHPBar->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteHPBar->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̘g
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̉��n
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̃s���`���̂��
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite(m_kSpriteDangerFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteDanger->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteDanger->SetPivot(imgData.Pivot);
                        // ��\���ɂ���
                        m_spriteDanger->Deactivate();
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // HP�o�[�̃f�B���C�A�j���[�V�����p��UI
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteDecrease = NewGO<CSpriteUI>();
                        m_spriteDecrease->LoadSprite(m_kSpriteDecreaaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteDecrease->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteDecrease->SetPivot(imgData.Pivot);
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
            if (m_kDangerLine > m_barWidthSize) {
                ChangeDangerUI(true);
            }
            else {
                ChangeDangerUI(false);
            }

            // �Q�[�W�̒����i�����j��K�p
            m_spriteHPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
            m_spriteDanger->SetScale({ m_barWidthSize,1.0f,1.0f });
            m_spriteDecrease->SetScale({ m_decreaseBarWidthSize,1.0f,1.0f });

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