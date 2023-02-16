#include "EventPiece.h"
#include "../UI/Story/ConversationPlayerInputDisable.h"
#include "EventManager.h"
#include "EventSetFuncPool.h"
#include "../Player/Player.h"

namespace nsAWA
{
	namespace nsEvent
	{
		const char* const CEventPiece::m_kCsvFileRootPath = "Assets/CSV/Event/EventConversation/";
		const float CEventPiece::m_kActionDist = 100.0f;

		bool CEventPiece::Start()
		{

			return true;
		}

		void CEventPiece::Update(float deltaTime)
		{
			if (IsClear())
			{
				return;
			}

			if (m_isStartEvent != true)
			{
				return;
			}


			switch (m_eventPieceType)
			{
			case EnEventPieceType::enNone:
				return;
				break;
			case EnEventPieceType::enSet:
				UpdateSet();
				break;
			case EnEventPieceType::enTrigger:
				break;
			case EnEventPieceType::enAction:
				UpdateAction();
				break;
			case EnEventPieceType::enConversation:
				UpdateConversation();
				break;
			}
			return;
		}

		void CEventPiece::OnDestroy()
		{
			m_trigger.Release();

			DeleteGO(m_conversation);
			m_conversation = nullptr;

			return;
		}

		void CEventPiece::Init(
			const std::string& eventName, 
			EnEventPieceType pieceType,
			int conversationCount,
			int triggerCount,
			int setFuncCount
		) noexcept
		{
			m_eventName = eventName;
			m_eventPieceType = pieceType;
			m_conversationCount = conversationCount;
			m_triggerCount = triggerCount;
			m_setFuncCount = setFuncCount;

			return;
		}

		void CEventPiece::StartEvent()
		{
			if (m_eventName.empty())
			{
				return;
			}

			m_isStartEvent = true;

			if (m_eventPieceType == EnEventPieceType::enTrigger)
			{
				const auto& map = CEventManager::GetInstance()->GetEventTriggerMap();
				std::string findName = m_eventName;
				findName += ('0' + m_triggerCount + 1);
				auto itr = map.find(findName);

				if (itr == map.end())
				{
					nsGameWindow::MessageBoxError(L"必要なイベントトリガーがレベルから読み込まれていません。");
					return;
				}

				m_position = itr->second.pos;
				constexpr float extent = 1.0f;
				CVector3 halfExtent = { extent,extent,extent };
				halfExtent.x *= itr->second.scale.x;
				halfExtent.y *= itr->second.scale.y;
				halfExtent.z *= itr->second.scale.z;

				m_trigger.InitAsBox(halfExtent, m_position);
				m_trigger.SetRotation(itr->second.rot);
				m_trigger.SetOnTriggerEnterFunc(
					[&](CExtendedDataForRigidActor* otherData) { OnTriggerEnter(otherData); });

			}
			else if (m_eventPieceType == EnEventPieceType::enConversation)
			{
				m_conversation = NewGO<nsUI::CConversationPlayerInputDisable>();
				std::string str = m_kCsvFileRootPath;
				str += m_eventName;
				str += ('0' + m_conversationCount + 1);
				str += ".csv";
				m_conversation->Init(
					nsUtils::GetWideStringFromString(str).c_str());
			}
			else if (m_eventPieceType == EnEventPieceType::enSet)
			{
				const auto& SetFuncListMap = 
					CEventManager::GetInstance()->GetEventSetFuncPool()->GetSetFuncListMap();

				auto itr = SetFuncListMap.find(m_eventName);
				if (itr == SetFuncListMap.end())
				{
					nsGameWindow::MessageBoxError(L"必要なSetFuncがPoolに登録されていません。");
					return;
				}

				m_setFunc = itr->second.at(m_setFuncCount);

			}


			return;
		}



		void CEventPiece::OnTriggerEnter(CExtendedDataForRigidActor* oterData)
		{
			if (oterData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayer)
			{
				return;
			}

			Clear();

			return;
		}

		void CEventPiece::UpdateAction()
		{
			const auto* playerRef = CEventManager::GetInstance()->GetPlayerRef();

			if (playerRef == nullptr)
			{
				return;
			}


			auto dist = playerRef->GetPosition() - m_position;

			if (dist.Length() > m_kActionDist)
			{
				return;
			}

			if (Input()->IsTrigger(EnActionMapping::enDecision))
			{
				Clear();
			}

			return;
		}

		void CEventPiece::UpdateConversation()
		{
			if (m_conversation == nullptr)
			{
				return;
			}

			if (m_conversation->IsEnd())
			{
				Clear();
				DeleteGO(m_conversation);
				m_conversation = nullptr;
			}

			return;
		}

		void CEventPiece::UpdateSet()
		{
			if (m_setFunc())
			{
				Clear();
			}

			return;
		}



	}
}