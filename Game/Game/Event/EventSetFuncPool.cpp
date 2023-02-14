#include "EventSetFuncPool.h"
#include "EventNameTable.h"
#include "../Scenes/OpeningScene.h"
#include "../GameLog/GameLog.h"

namespace nsAWA
{
	namespace nsEvent
	{
		CEventSetFuncPool::CEventSetFuncPool()
		{
			const char* eventName = GetEventNameFromTable(EnEventNameType::enGoddesAndAWTransfer);
			m_setFuncListMap[eventName].reserve(2);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					if (nsScene::COpeningScene::IsInitialOpening())
					{
						return true;
					}
					return false;
				}
			);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					return Input()->IsTrigger(EnActionMapping::enDecision);
				}
			);

			eventName = GetEventNameFromTable(EnEventNameType::enTrainingWithHRA);
			m_setFuncListMap[eventName].reserve(1);
			m_setFuncListMap[eventName].emplace_back(
				[]()->bool
				{
					nsGameLog::CGameLog::GetInstance()->AddGameLog("20000G‚ð“üŽè");
					return true;
				}
			);




			return;
		}

		bool CEventSetFuncPool::Start()
		{
			return true;
		}

		void CEventSetFuncPool::Update(float deltaTime)
		{

			return;
		}

		void CEventSetFuncPool::OnDestroy()
		{

			return;
		}




	}
}