#include "YonemaEnginePreCompile.h"
#include "InnWindowUI.h"
#include "../../../UserData.h"
#include "../../../Network/NetworkManager.h"
#include "../../../Feature/FeatureBuilder.h"
#include "../../../Player/Player.h"
#include "../../../Event/ProgressManagement/EventSaveData.h"

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
			if (abs(Input()->GetVirtualAxis(EnAxisMapping::enForward)) >= 0.8f && m_canChangeItem == true)
			{
				ChengeSelectingItem();

				m_canChangeItem = false;
			}
			
			//Exit
			if (Input()->IsTrigger(EnActionMapping::enCancel))
			{
				ExitUI();
			}

			//OK
			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				StartExecute();
			}

			if (abs(Input()->GetVirtualAxis(EnAxisMapping::enForward)) < 0.8f)
			{
				m_canChangeItem = true;
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
				//�x��

				//�x�ގ��̉����~����?

				nsPlayer::CPlayer* player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

				nsFeature::CFeatureBuilder healFeature;

				std::vector<std::string> featureVec;
				featureVec.push_back("Heal");
				featureVec.push_back("HP");
				featureVec.push_back("Ratio");
				featureVec.push_back("100");

				std::list<std::vector<std::string>> feature;
				feature.push_back(featureVec);

				healFeature.CreateFeature(player,player,feature);

			}
			else
			{
				//�Z�[�u

				//�Z�[�u���鎞�̉����~����?

				//���[�U�[�f�[�^�̃Z�[�u
				CUserData userDataSave;
				userDataSave.Save();

				//�C�x���g�f�[�^�̃Z�[�u
				nsEvent::CEventSaveData eventDataSave;
				eventDataSave.Save();

				//�Z�[�u�����f�[�^���l�b�g���[�N�ɃA�b�v���[�h
				nsNetwork::CNetworkManager::GetInstance()->UploadSaveData();
			}

			m_level.PlayAnimation("FadeEnd");
		}
	}
}