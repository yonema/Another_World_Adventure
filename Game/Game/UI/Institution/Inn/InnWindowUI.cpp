#include "YonemaEnginePreCompile.h"
#include "InnWindowUI.h"

namespace nsAWA
{
	namespace nsUI
	{
		bool CInnWindowUI::Start()
		{
			m_level.Load(m_kInnWindowFilePath);

			//�A�j���[�V�����C�x���g�̏�����
			RegisterAnimationEvents();

			m_playingAnimation = true;
			m_level.PlayAnimation("InnAppear");
			return true;
		}

		void CInnWindowUI::OnDestroy()
		{
		}

		void CInnWindowUI::RegisterAnimationEvents()
		{
			m_level.RegisterAnimationEvent("InnAppear", "Appeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_level.PlayAnimation("RestAppear");
				}
			);

			m_level.RegisterAnimationEvent("RestAppear", "Appeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_level.PlayAnimation("SaveAppear");
				}
			);

			m_level.RegisterAnimationEvent("SaveAppear", "Appeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_level.PlayAnimation("RestSelect");
					m_selecting = EnSelectingItem::enRest;

					m_playingAnimation = false;
				}
			);

			m_level.RegisterAnimationEvent("SaveSelect", "SelectEnd", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_playingAnimation = false;
				}
			);

			m_level.RegisterAnimationEvent("RestSelect", "SelectEnd", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_playingAnimation = false;
				}
			);

			m_level.RegisterAnimationEvent("InnDisappear", "Disappeared", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_endFlag = true;
				}
			);

			m_level.RegisterAnimationEvent("FadeStart", "End", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					Execute();
				}
			);

			m_level.RegisterAnimationEvent("FadeEnd", "End", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_playingAnimation = false;
				}
			);
		}

		void CInnWindowUI::Update(float deltaTime)
		{
			if (m_playingAnimation == true)
			{
				return;
			}

			//ChengeSelect
			if (Keyboard()->IsTrigger(EnKeyButton::en8))
			{
				ChengeSelectingItem();
			}
			
			//Exit
			if (Keyboard()->IsTrigger(EnKeyButton::en9))
			{
				ExitUI();
			}

			//OK
			if (Keyboard()->IsTrigger(EnKeyButton::en0))
			{
				StartExecute();
			}
		}

		void CInnWindowUI::ChengeSelectingItem()
		{
			//���ݑI�𒆂̃A�C�e���ɂ���đI��؂�ւ�
			if (m_selecting == EnSelectingItem::enRest)
			{
				m_selecting = EnSelectingItem::enSave;

				m_playingAnimation = true;

				m_level.PlayAnimation("SaveSelect");
				m_level.PlayAnimation("RestDeselect");
			}
			else
			{
				m_selecting = EnSelectingItem::enRest;

				m_playingAnimation = true;

				m_level.PlayAnimation("RestSelect");
				m_level.PlayAnimation("SaveDeselect");
			}
		}

		void CInnWindowUI::ExitUI()
		{
			//���ݑI�𒆂̃{�^�������̑傫���ɖ߂��B
			std::string selectingItemName = "";

			if (m_selecting == EnSelectingItem::enRest)
			{
				selectingItemName = "Rest";
			}
			else
			{
				selectingItemName = "Save";
			}

			std::string callEventName = selectingItemName + "Deselect";

			//���̑傫���ɖ߂��I�������{�^���E�w�i���폜����B
			m_level.RegisterAnimationEvent(callEventName.c_str(), "DeselectEnd", [this](const nsYMEngine::nsGraphics::nsAnimations2D::SAnimation2DFrameData& frameData)
				{
					m_level.PlayAnimation("InnDisappear");
					m_level.PlayAnimation("ButtonDisappear");
				}
			);

			m_playingAnimation = true;
			m_level.PlayAnimation(callEventName.c_str());
		}

		void CInnWindowUI::StartExecute()
		{
			m_playingAnimation = true;

			m_level.PlayAnimation("FadeStart");
		}

		void CInnWindowUI::Execute()
		{
			if (m_selecting == EnSelectingItem::enRest)
			{
				nsGameWindow::MessageBoxWarning(L"�x�݂܂����B");
				//Execute Rest
			}
			else
			{
				nsGameWindow::MessageBoxWarning(L"�Z�[�u���܂����B");
				//Execute Save
			}

			m_level.PlayAnimation("FadeEnd");
		}
	}
}