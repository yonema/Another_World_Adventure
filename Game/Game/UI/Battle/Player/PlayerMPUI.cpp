#include "YonemaEnginePreCompile.h"
#include "PlayerMPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerMPUI::m_kSpriteMPBarFilePath = 
            "Assets/Image/FitnessBar/Player/Bar_MP.png";
        const char* CPlayerMPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CPlayerMPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";

        bool CPlayerMPUI::Start()
        {
            return true;
        }

        void CPlayerMPUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                //�I�u�W�F�N�g�l�[����"player_kari"�Ɠ�����������
                    if (imgData.EqualObjectName(L"�v���C���[��MP�o�[") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteMPBar->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteMPBar->SetPivot(imgData.pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��MP�o�[�̘g
                    if (imgData.EqualObjectName(L"�v���C���[��MP�o�[�̘g") == true)
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
                    // �v���C���[��MP�o�[�̉��n
                    if (imgData.EqualObjectName(L"�v���C���[��MP�̉��n") == true)
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
            m_spriteMPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}