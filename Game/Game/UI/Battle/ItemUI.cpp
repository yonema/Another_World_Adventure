#include "YonemaEnginePreCompile.h"
#include "ItemUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CItemUI::Start()
        {
            return true;
        }

        void CItemUI::LoadLevel(const char* tdlFilePath)
        {
            /*
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                //�I�u�W�F�N�g�l�[����"player_kari"�Ɠ�����������
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite("�t�@�C���p�X");
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteMPBar->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteMPBar->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̘g
                    else if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite("�t�@�C���p�X");
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteFrame->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̉��n
                    else if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite("�t�@�C���p�X");
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �v���C���[��HP�o�[�̃s���`���̂��
                    else if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite("�t�@�C���p�X");
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteDanger->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteDanger->SetPivot(imgData.Pivot);
                        // ��\���ɂ���
                        m_spriteDanger->Deactivate();
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });
                */
        }

        void CItemUI::OnDestroy()
        {
            //DeleteGO(m_spriteMPBar);
            //DeleteGO(m_spriteFrame);
            //DeleteGO(m_spriteBase);
            //DeleteGO(m_spriteDanger);
        }

        void CItemUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // MP�o�[�̃A�j���[�V����
            Animation();

        }

        void CItemUI::Animation()
        {
            // �Q�[�W�̒����i�����j��K�p
            //m_spriteMPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}