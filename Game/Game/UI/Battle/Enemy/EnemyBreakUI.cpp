#include "YonemaEnginePreCompile.h"
#include "EnemyBreakUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBreakUI::m_kSpriteBreakBarFilePath =
            "Assets/Image/FitnessBar/Enemy/Gauge_Break.png";
        const char* CEnemyBreakUI::m_kSpriteBreakFilePath =
            "Assets/Image/FitnessBar/Enemy/Break_GaugeMax.png";
        const char* CEnemyBreakUI::m_kSpriteBreakReductionFilePath =
            "Assets/Image/FitnessBar/Enemy/Break_GaugeDecrease.png";
        const char* CEnemyBreakUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Enemy/Gauge_Break_Groundwork.png";

        bool CEnemyBreakUI::Start()
        {
            return true;
        }

        void CEnemyBreakUI::LoadLevel(const char* tdlFilePath, const CVector2& basePosition)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �u���C�N�Q�[�W
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBreakBar = NewGO<CSpriteUI>();
                        m_spriteBreakBar->LoadSprite(m_kSpriteBreakBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakBar->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakBar->SetPivot(imgData.Pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBreakBar = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̘g
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBreak = NewGO<CSpriteUI>();
                        m_spriteBreak->LoadSprite(m_kSpriteBreakFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBreak->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBreak->SetPivot(imgData.Pivot);
                        // ��\���ɂ���
                        m_spriteBreak->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBreak = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̉��n
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBreakReduction = NewGO<CSpriteUI>();
                        m_spriteBreakReduction->LoadSprite(m_kSpriteBreakReductionFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakReduction->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakReduction->SetPivot(imgData.Pivot);
                        // ��\���ɂ���
                        m_spriteBreakReduction->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBreakReduction = basePosition - imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̃s���`���̂��
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
                });
        }

        void CEnemyBreakUI::OnDestroy()
        {
            DeleteGO(m_spriteBreakBar);
            DeleteGO(m_spriteBreak);
            DeleteGO(m_spriteBreakReduction);
            DeleteGO(m_spriteBase);
        }

        void CEnemyBreakUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // HP�o�[�̃A�j���[�V����
            Animation();

        }

        void CEnemyBreakUI::Animation()
        {
            // �Q�[�W�̒����i�����j��K�p
            m_spriteBreakBar->SetScale({ 1.0f,m_barPercentage,1.0f });
        }

        void CEnemyBreakUI::SetUIPosition(const CVector2& position)
        {
            m_spriteBreakBar->SetPosition(position + m_correctionAmountBreakBar);
            m_spriteBreak->SetPosition(position + m_correctionAmountBreak);
            m_spriteBreakReduction->SetPosition(position + m_correctionAmountBreakReduction);
            m_spriteBase->SetPosition(position + m_correctionAmountBase);
        }
    }
}