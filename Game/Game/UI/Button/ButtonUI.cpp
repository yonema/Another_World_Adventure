#include "YonemaEnginePreCompile.h"
#include "ButtonUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CButtonUI::m_kSpriteButtonFilePath[EnButtonUI::enMaxButtonUI] =
        {
            "Assets/Image/ButtonRelated/Button_A.png",
            "Assets/Image/ButtonRelated/Button_B.png",
            "Assets/Image/ButtonRelated/Button_X.png",
            "Assets/Image/ButtonRelated/Button_Y.png",
            "Assets/Image/ButtonRelated/Button_L.png",
            "Assets/Image/ButtonRelated/Button_R.png",
            "Assets/Image/ButtonRelated/Trigger_L.png",
            "Assets/Image/ButtonRelated/Trigger_R.png",
        };

        bool CButtonUI::Start()
        {
            return true;
        }

        void CButtonUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // A�{�^��
                    if (imgData.EqualObjectName(L"A�{�^��") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enA, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // B�{�^��
                    if (imgData.EqualObjectName(L"B�{�^��") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enB, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // X�{�^��
                    if (imgData.EqualObjectName(L"X�{�^��") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enX, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // Y�{�^��
                    if (imgData.EqualObjectName(L"Y�{�^��") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enY, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // L�{�^��
                    if (imgData.EqualObjectName(L"L�{�^��") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enBL, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // R�{�^��
                    if (imgData.EqualObjectName(L"R�{�^��") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enBR, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // L�g���K�[
                    if (imgData.EqualObjectName(L"L�g���K�[") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enTL, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // R�g���K�[
                    if (imgData.EqualObjectName(L"R�g���K�[") == true)
                    {
                        // �Ή������{�^����UI��ǂݍ���
                        LoadButtonSprite(EnButtonUI::enTR, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CButtonUI::LoadButtonSprite(const int buttonUINum, LevelObjectData& imgData)
        {
            // UI�N���X���쐬
            m_spriteButton = NewGO<CSpriteUI>();
            m_spriteButton->LoadSprite(m_kSpriteButtonFilePath[buttonUINum]);
            // �|�W�V���������[�h�����摜�Ɠ����ɂ���
            m_spriteButton->SetPosition(imgData.position);
            // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
            m_spriteButton->SetPivot(imgData.pivot);
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