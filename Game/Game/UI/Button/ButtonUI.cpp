#include "YonemaEnginePreCompile.h"
#include "ButtonUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CButtonUI::m_kSpriteButtonFilePath[EnButtonUI::enMaxButtonUI] =
        {
            "Assets/Images/ButtonRelated/Button_A.png",
            "Assets/Images/ButtonRelated/Button_B.png",
            "Assets/Images/ButtonRelated/Button_X.png",
            "Assets/Images/ButtonRelated/Button_Y.png",
            "Assets/Images/ButtonRelated/Button_L.png",
            "Assets/Images/ButtonRelated/Button_R.png",
            "Assets/Images/ButtonRelated/Trigger_L.png",
            "Assets/Images/ButtonRelated/Trigger_R.png",
        };

        bool CButtonUI::Start()
        {
            return true;
        }

        void CButtonUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // A�{�^��
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enA, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // B�{�^��
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enB, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // X�{�^��
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enX, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // Y�{�^��
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enY, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // L�{�^��
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enBL, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // R�{�^��
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enBR, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // L�g���K�[
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enTL, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // R�g���K�[
                    if ("" == imgData.Name)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enTR, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CButtonUI::LoadButtonSprite(const int buttonUINum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UI�N���X���쐬
            m_spriteButton = NewGO<CSpriteUI>();
            m_spriteButton->LoadSprite(m_kSpriteButtonFilePath[buttonUINum]);
            // �|�W�V���������[�h�����摜�Ɠ����ɂ���
            m_spriteButton->SetPosition(imgData.Position);
            // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
            m_spriteButton->SetPivot(imgData.Pivot);
        }

        void CButtonUI::OnDestroy()
        {
            DeleteGO(m_spriteButton);
        }

        void CButtonUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // MP�o�[�̃A�j���[�V����
            Animation();

        }

        void CButtonUI::Animation()
        {

        }
    }
}