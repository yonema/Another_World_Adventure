#include "YonemaEnginePreCompile.h"
#include "EnemyHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyHPUI::m_kSpriteHPBarFilePath = 
            "Assets/Images/FitnessBar/Common/Bar_HP.png";
        const char* CEnemyHPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CEnemyHPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";
        const char* CEnemyHPUI::m_kSpriteDangerFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_Danger.png";

        bool CEnemyHPUI::Start()
        {
            return true;
        }

        void CEnemyHPUI::LoadLevel(const char* tdlFilePath, const CVector2& basePosition)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �G��HP�o�[
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteHPBar->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteHPBar->SetPivot(imgData.Pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountHPBar = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̘g
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPivot(imgData.Pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountFrame = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̉��n
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPivot(imgData.Pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBase = basePosition - imgData.Position;
                        
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̃s���`���̂��
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

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountDanger = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
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
            m_spriteHPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
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