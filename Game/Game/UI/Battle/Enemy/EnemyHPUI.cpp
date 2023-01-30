#include "YonemaEnginePreCompile.h"
#include "EnemyHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyHPUI::m_kSpriteHPBarFilePath = 
            "Assets/Image/FitnessBar/Common/Bar_HP.png";
        const char* CEnemyHPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CEnemyHPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";
        const char* CEnemyHPUI::m_kSpriteDangerFilePath =
            "Assets/Image/FitnessBar/Common/Bar_HP_Danger.png";

        bool CEnemyHPUI::Start()
        {
            return true;
        }

        void CEnemyHPUI::LoadLevel(const char* tdlFilePath, const CVector2& basePosition)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                //�I�u�W�F�N�g�l�[����"player_kari"�Ɠ�����������
                    if (imgData.EqualObjectName(L"�G��HP�o�[") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteHPBar->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteHPBar->SetPivot(imgData.pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountHPBar = basePosition - imgData.position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̘g
                    if (imgData.EqualObjectName(L"�G��HP�o�[�̘g") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPivot(imgData.pivot);

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountFrame = basePosition - imgData.position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �G��HP�o�[�̉��n
                    if (imgData.EqualObjectName(L"�G��HP�̉��n") == true)
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
                    // �G��HP�o�[�̃s���`���̂��
                    if (imgData.EqualObjectName(L"�G��HP�̃s���`��") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite(m_kSpriteDangerFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteDanger->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteDanger->SetPivot(imgData.pivot);
                        // ��\���ɂ���
                        m_spriteDanger->Deactivate();

                        // UI�ʒu�̕␳�l���擾
                        m_correctionAmountDanger = basePosition - imgData.position;

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
    }
}