#include "YonemaEnginePreCompile.h"
#include "GuildWindowUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CGuildWindowUI::m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber] =
        {
            "Assets/Images/Institution/Guild/Window_1.png",
            "Assets/Images/Institution/Guild/Window_2.png"
        };

        bool CGuildWindowUI::Start()
        {
            return true;
        }

        void CGuildWindowUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �E�B���h�E�P
                    if ("" == imgData.Name)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_1, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �E�B���h�E�Q
                    if ("" == imgData.Name)
                    {
                        // �Ή������E�B���h�E��UI��ǂݍ���
                        LoadWindowSprite(EnWindowNumber::enWindow_2, imgData);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CGuildWindowUI::LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData)
        {
            // UI�N���X���쐬
            m_spriteWindow[windowNum] = NewGO<CSpriteUI>();
            m_spriteWindow[windowNum]->LoadSprite(m_kSpriteWindowFilePath[windowNum]);
            // �|�W�V���������[�h�����摜�Ɠ����ɂ���
            m_spriteWindow[windowNum]->SetPosition(imgData.Position);
            // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
            m_spriteWindow[windowNum]->SetPivot(imgData.Pivot);
        }

        void CGuildWindowUI::OnDestroy()
        {
            for (auto& forNum : m_spriteWindow) {
                DeleteGO(forNum);
            }
        }

        void CGuildWindowUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������


        }

        void CGuildWindowUI::Animation()
        {

        }
    }
}