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


			//�E�B���h�E��������A�j���[�V�������I���������̃C�x���g���L�q
			m_level.RegisterAnimationEvent("WindowDisappear", "Disappeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					DeleteGO(this);
				}
			);

			return true;
		}

		void CConversationWindowUI::OnDestroy()
		{
			m_text.Release();
		}

		void CConversationWindowUI::Update(float deltaTime)
		{
			if (m_text.IsInited() == false)
			{
				return;
			}

			m_text.Update(deltaTime);

			if (Gamepad()->IsTrigger(EnPadButton::enA) || Keyboard()->IsTrigger(EnKeyButton::enJ))
			{
				m_text.Next();
				m_level.PlayAnimation("Pressed");

				if (m_text.IsShowAllSentence())
				{
					m_text.Release();
					m_level.PlayAnimation("WindowDisappear");
					m_level.PlayAnimation("ButtonDisappear");
				}
			}
		}
	}
}