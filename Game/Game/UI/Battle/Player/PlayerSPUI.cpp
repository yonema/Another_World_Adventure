#include "YonemaEnginePreCompile.h"
#include "PlayerSPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerSPUI::m_kSpriteSPBarFilePath =
            "Assets/Image/FitnessBar/Player/Bar_SP.png";
        const char* CPlayerSPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CPlayerSPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";

        bool CPlayerSPUI::Start()
        {
            return true;
        }

        void CPlayerSPUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                //�I�u�W�F�N�g�l�[����"player_kari"�Ɠ�����������
                    if (imgData.EqualObjectName(L"�v���C���[��SP�o�[") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteSPBar = NewGO<CSpriteUI>();
                        m_spriteSPBar->LoadSprite(m_kSpriteSPBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteSPBar->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteSPBar->SetPivot(imgData.pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��SP�o�[�̘g
                    if (imgData.EqualObjectName(L"�v���C���[��SP�o�[�̘g") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPivot(imgData.pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��SP�o�[�̉��n
                    if (imgData.EqualObjectName(L"�v���C���[��SP�̉��n") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPivot(imgData.pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CPlayerSPUI::OnDestroy()
        {
            DeleteGO(m_spriteSPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
        }

        void CPlayerSPUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // SP�o�[�̃A�j���[�V����
            Animation();

        }

        void CPlayerSPUI::Animation()
        {
            // �Q�[�W�̒����i�����j��K�p
            m_spriteSPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}