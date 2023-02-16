#include "ConversationPlayerInputDisable.h"
#include "../../Player/PlayerManager.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CConversationPlayerInputDisable::Start()
        {
            return true;
        }

        void CConversationPlayerInputDisable::OnDestroy()
        {
            DeleteGO(m_conversationWindowUI);
            m_conversationWindowUI = nullptr;

            auto* playerManager = nsPlayer::CPlayerManager::GetInstance();
            if (playerManager == nullptr)
            {
                return;
            }
            playerManager->NotifyObserver(
                nsPlayer::nsObserver::EnObserverEvent::enInputEnable);

            return;
        }

        void CConversationPlayerInputDisable::Update(float deltaTime)
        {
            return;
        }


        CConversationPlayerInputDisable::CConversationPlayerInputDisable()
        {
            m_conversationWindowUI = NewGO<CConversationWindowUI>();

            return;
        }

        void CConversationPlayerInputDisable::Init(const wchar_t* csvFilePath)
        {
            if (m_conversationWindowUI == nullptr)
            {
                return;
            }

            m_conversationWindowUI->InitConvesationCSV(csvFilePath);

            auto* playerManager = nsPlayer::CPlayerManager::GetInstance();
            if (playerManager == nullptr)
            {
                return;
            }

            playerManager->NotifyObserver(
                nsPlayer::nsObserver::EnObserverEvent::enInputDisable);

            return;
        }



    }
}