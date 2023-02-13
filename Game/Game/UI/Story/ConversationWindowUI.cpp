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


			//ウィンドウが消えるアニメーションが終了した時のイベントを記述
			m_level.RegisterAnimationEvent("WindowDisappear", "Disappeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_endFlag = true;
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
			if (m_text.IsInited() == false || m_endFlag)
			{
				return;
			}

			m_text.Update(deltaTime);

			
			if (Input()->IsTrigger(EnActionMapping::enDecision))
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