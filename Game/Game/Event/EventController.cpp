#include "EventController.h"
#include "EventManager.h"
#include "EventFlow.h"

namespace nsAWA
{
	namespace nsEvent
	{
		bool CEventController::Start()
		{
			InitCurrentEventFlowMap();

			return true;
		}

		void CEventController::Update(float deltaTime)
		{
			bool reInit = false;

			auto itr = m_currentEventFlowMap.begin();
			while(itr != m_currentEventFlowMap.end())
			{
				if (itr->second->IsClear())
				{
					reInit = true;
					DeleteGO(itr->second);
					itr = m_currentEventFlowMap.erase(itr);
				}
				else
				{
					itr++;
				}
			}

			if (reInit)
			{
				InitCurrentEventFlowMap();
			}

			return;
		}

		void CEventController::OnDestroy()
		{

			return;
		}

		void CEventController::InitCurrentEventFlowMap()
		{
			const auto& latestEvents = CEventProgressManager::GetInstance()->GetLatestEvents();

			for (const auto& latestEvent : latestEvents)
			{
				if (latestEvent->GetProgressState() == EnEventState::enProgress)
				{
					auto itr = m_currentEventFlowMap.find(latestEvent->GetName());
					if (itr != m_currentEventFlowMap.end())
					{
						// ‚·‚Å‚É‚ ‚é
						continue;
					}

					auto* newEvent = NewGO<CEventFlow>(latestEvent->GetName().c_str());
					newEvent->Init(latestEvent->GetName());
					m_currentEventFlowMap.emplace(latestEvent->GetName(), newEvent);
				}
			}

			return;
		}





	}
}