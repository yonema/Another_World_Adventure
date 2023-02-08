#include "YonemaEnginePreCompile.h"
#include "ConversationWindowUI.h"

#include "../SpriteUI.h"
#include <sstream>


namespace nsAWA
{
	namespace nsUI
	{

		bool CConversationWindowUI::Start()
		{
			m_level.Load(m_kSpriteWindowFilePath);

			m_level.PlayAnimation("WindowAppear");
			m_level.PlayAnimation("ButtonAppear");
			m_text.Init(L"Assets/CSV/Conversation/ConversationSample.csv");

			return true;
		}

		void CConversationWindowUI::LoadLevel(const char* tdlFilePath)
		{
			m_level.Load(m_kSpriteWindowFilePath);
		}

		void CConversationWindowUI::OnDestroy()
		{
		}

		void CConversationWindowUI::Update(float deltaTime)
		{
			if (m_text.IsInited() == true)
			{
				m_text.Update(deltaTime);

				if (Keyboard()->IsTrigger(EnKeyButton::enJ))
				{
					m_text.Next();
					m_level.PlayAnimation("Pressed");
				}
			}

		}
	}
}