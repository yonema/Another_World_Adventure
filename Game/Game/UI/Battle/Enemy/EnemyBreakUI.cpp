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
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                //�I�u�W�F�N�g�l�[����"player_kari"�Ɠ�����������
                    if (imgData.EqualObjectName(L"�u���C�N�Q�[�W") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteBreakBar = NewGO<CSpriteUI>();
                        m_spriteBreakBar->LoadSprite(m_kSpriteBreakBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakBar->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakBar->SetPivot(imgData.pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBreakBar = basePosition - imgData.position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̘g
                    if (imgData.EqualObjectName(L"�u���C�N����Break!") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteBreak = NewGO<CSpriteUI>();
                        m_spriteBreak->LoadSprite(m_kSpriteBreakFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBreak->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBreak->SetPivot(imgData.pivot);
                        // ��\���ɂ���
                        m_spriteBreak->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBreak = basePosition - imgData.position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̉��n
                    if (imgData.EqualObjectName(L"�u���C�N�Q�[�W��������Break!") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteBreakReduction = NewGO<CSpriteUI>();
                        m_spriteBreakReduction->LoadSprite(m_kSpriteBreakReductionFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakReduction->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBreakReduction->SetPivot(imgData.pivot);
                        // ��\���ɂ���
                        m_spriteBreakReduction->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBreakReduction = basePosition - imgData.position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̃s���`���̂��
                    if (imgData.EqualObjectName(L"�u���C�N�Q�[�W�̉��n") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPivot(imgData.pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountBase = basePosition - imgData.position;

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
    }
}