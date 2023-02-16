#pragma once
#include "ConversationWindowUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        class CConversationPlayerInputDisable : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CConversationPlayerInputDisable();
            ~CConversationPlayerInputDisable() = default;

            void Init(const wchar_t* csvFilePath);

            constexpr bool IsEnd() const noexcept
            {
                return m_conversationWindowUI ? m_conversationWindowUI->IsEnd() : false;
            }

        private:
            CConversationWindowUI* m_conversationWindowUI = nullptr;
        };

    }
}