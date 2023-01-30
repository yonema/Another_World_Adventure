#include "YonemaEnginePreCompile.h"
#include "InnStorehouseWindowUI.h"

#include "../../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CInnStorehouseWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Image/Institution/Inn/Storehouse/Window_1.png",
            "Assets/Image/Institution/Inn/Storehouse/Window_2.png",
            "Assets/Image/Institution/Inn/Storehouse/Window_3.png",
            "Assets/Image/Institution/Inn/Storehouse/Window_4.png"
        };

        bool CInnStorehouseWindowUI::Start()
        {
            return true;
        }

        void CInnStorehouseWindowUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �E�B���h�E�P
                    if (imgData.EqualObjectName(L"�E�B���h�E�P") == true)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_1, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�Q
                    if (imgData.EqualObjectName(L"�E�B���h�E�Q") == true)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�R
                    if (imgData.EqualObjectName(L"�E�B���h�E�R") == true)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_3, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�S
                    if (imgData.EqualObjectName(L"�E�B���h�E�S") == true)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_4, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CInnStorehouseWindowUI::LoadWindowSprite(const int windowNum, LevelObjectData& imgData)
        {
            // UI�N���X���쐬
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // �|�W�V���������[�h�����摜�Ɠ����ɂ���
            m_spriteWindow[windowNum]->SetPosition(imgData.position);
            // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
            m_spriteWindow[windowNum]->SetPivot(imgData.pivot);
        }

        void CInnStorehouseWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CInnStorehouseWindowUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������


        }

        void CInnStorehouseWindowUI::Animation()
        {

        }
    }
}