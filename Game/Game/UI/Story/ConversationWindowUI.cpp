#include "YonemaEnginePreCompile.h"
#include "ConversationWindowUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CConversationWindowUI::m_kSpriteWindowFilePath =
            "�t�@�C���p�X";

        bool CConversationWindowUI::Start()
        {
            return true;
        }

        void CConversationWindowUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �E�B���h�E�P
                    if (imgData.EqualObjectName(L"�E�B���h�E�P") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteWindow = NewGO<CSpriteUI>();
                        m_spriteWindow->LoadSprite(m_kSpriteWindowFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteWindow->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteWindow->SetPivot(imgData.pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CConversationWindowUI::OnDestroy()
        {
            DeleteGO(m_spriteWindow);
        }

        void CConversationWindowUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������


        }

        void CConversationWindowUI::Animation()
        {

        }
    }
}