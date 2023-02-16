#include "Inn.h"
#include "../Player/PlayerManager.h"

namespace nsAWA
{
	namespace nsFacility
	{
		bool CInn::Start()
		{
			
			m_enterFont = NewGO<CFontRenderer>();

			SFontParameter initParam;
			initParam.position = CVector2(0.0f, 250.0f);
			initParam.pivot = CVector2(0.5f, 0.5f);
			initParam.text = L"宿屋";
			initParam.scale = 0.0f;

			m_enterFont->Init(initParam);
			
			return true;
		}

		void CInn::OnDestroy()
		{

			return;
		}

		void CInn::Update(float deltaTime)
		{

			return;
		}

		void CInn::OnTriggerEnter(CExtendedDataForRigidActor* otherData)
		{
			auto attr = otherData->GetPhysicsAttribute();

			if (attr != EnPhysicsAttributes::enPlayer)
			{
				return;
			}

			m_enterFont->SetScale(1.0f);
		}

		void CInn::OnTriggerStay(CExtendedDataForRigidActor* otherData)
		{
			auto attr = otherData->GetPhysicsAttribute();

			if (attr != EnPhysicsAttributes::enPlayer)
			{
				return;
			}

			//入るボタンを押した時に、プレイヤーロックして宿のUIを表示
			if (m_state == EnFacilityState::enClose && Input()->IsTrigger(EnActionMapping::enDecision))
			{
				m_state = EnFacilityState::enOpen;
				m_enterFont->SetScale(0.0f);

				auto* playerManager = nsPlayer::CPlayerManager::GetInstance();
				if (playerManager != nullptr)
				{
					playerManager->NotifyObserver(
						nsPlayer::nsObserver::EnObserverEvent::enInputDisable);
				}

				//宿表示
				m_windowUI = NewGO<nsUI::CInnWindowUI>();
			}


			if (m_windowUI != nullptr && m_windowUI->IsEnd() == true)
			{
				DeleteGO(m_windowUI);
				m_windowUI = nullptr;

				auto* playerManager = nsPlayer::CPlayerManager::GetInstance();
				if (playerManager != nullptr)
				{
					playerManager->NotifyObserver(
						nsPlayer::nsObserver::EnObserverEvent::enInputEnable);
				}

				m_enterFont->SetScale(1.0f);
			}
		}

		void CInn::OnTriggerExit(CExtendedDataForRigidActor* otherData)
		{
			auto attr = otherData->GetPhysicsAttribute();

			if (attr != EnPhysicsAttributes::enPlayer)
			{
				return;
			}

			//入るボタンの画像非表示
			m_enterFont->SetScale(0.0f);
		}
	}
}