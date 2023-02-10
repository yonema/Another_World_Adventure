#pragma once
#include "ConversationTextUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        class CConversationWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

            /**
             * @brief ��b��CSV�t�@�C�����Z�b�g�@�K���ĂԂ��ƁB
             * @param csvFilePath ��b��CSV�t�@�C���p�X
            */
            void InitConvesationCSV(const wchar_t* csvFilePath)
            {
                m_text.Init(csvFilePath);
            }

            constexpr bool IsEnd() const noexcept
            {
                return m_endFlag;
            }

        public:
            CConversationWindowUI() = default;
            ~CConversationWindowUI() = default;
        private: // constant data member
            const char* m_kSpriteWindowFilePath = "Assets/Level2D/LevelFiles/ConversationWindow.tdl";
        private: // data member
            nsLevel2D::CLevel2D m_level;    //��b�E�B���h�E�̃��x��
            CConversationTextUI m_text;     //��b�e�L�X�g�̕\���N���X
            bool m_endFlag = false;
        };
    }
}