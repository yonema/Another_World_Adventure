#include "YonemaEnginePreCompile.h"
#include "MenuItemWindowUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CMenuItemWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Image/Menu/Item/Window_1.png",
            "Assets/Image/Menu/Item/Window_2.png",
            "Assets/Image/Menu/Item/Window_3.png"
        };

        bool CMenuItemWindowUI::Start()
        {
            return true;
        }

        void CMenuItemWindowUI::LoadLevel(const char* tdlFilePath)
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
                });
        }

        void CMenuItemWindowUI::LoadWindowSprite(const int windowNum, LevelObjectData& imgData)
        {
            // UI�N���X���쐬
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // �|�W�V���������[�h�����摜�Ɠ����ɂ���
            m_spriteWindow[windowNum]->SetPosition(imgData.position);
            // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
            m_spriteWindow[windowNum]->SetPivot(imgData.pivot);
        }

        void CMenuItemWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CMenuItemWindowUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������


        }

        void CMenuItemWindowUI::Animation()
        {

        }
    }
}