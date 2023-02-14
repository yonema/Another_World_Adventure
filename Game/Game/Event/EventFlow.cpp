#include "EventFlow.h"
#include "EventManager.h"

namespace nsAWA
{
	namespace nsEvent
	{
		bool CEventFlow::Start()
		{
			return true;
		}

		void CEventFlow::Update(float deltaTime)
		{
			if (m_isClear)
			{
				return;
			}

			if (m_eventPieceArray.empty())
			{
				return;
			}

			if (m_eventPieceArray.at(m_currentPieceIdx) == nullptr)
			{

			}

			if (m_eventPieceArray.at(m_currentPieceIdx)->IsClear() != true)
			{
				return;
			}
			DeleteGO(m_eventPieceArray.at(m_currentPieceIdx));
			m_eventPieceArray.at(m_currentPieceIdx) = nullptr;
			CEventProgressManager::GetInstance()->ProgressEvent(m_eventName);
			m_currentPieceIdx++;

			if (m_currentPieceIdx >= m_eventPieceArray.size())
			{
				m_isClear = true;
				return;
			}

			m_eventPieceArray.at(m_currentPieceIdx)->StartEvent();

			return;
		}

		void CEventFlow::OnDestroy()
		{
			Release();


			return;
		}

		void CEventFlow::Init(const std::string& eventName)
		{
			Release();

			auto state = CEventProgressManager::GetInstance()->GetProgressState(eventName);
			if (state != EnEventState::enProgress)
			{
				// 進行可能のイベントじゃない
				return;
			}

			const auto& eventMatMap = CEventManager::GetInstance()->GetEventMaterialMap();
			auto itr = eventMatMap.find(eventName);

			if (itr == eventMatMap.end())
			{
				// イベントが見つからない
				return;
			}

			m_eventName = eventName;
			m_pieceTypeListRef = &itr->second.pieceTypeList;
			m_eventPieceArray.reserve(m_pieceTypeListRef->size());

			int conversationCount = 0;
			int triggerCount = 0;
			int setFuncCount = 0;
			std::list<CEventPiece*> setPieceTmp = {};

			auto pieceTypeItr = m_pieceTypeListRef->begin();

			for (int i = 0; i < m_pieceTypeListRef->size(); i++)
			{
				auto* piece = NewGO<CEventPiece>();
				int convIdx = -1;
				int triggerIdx = -1;
				int setFuncIdx = -1;
				if (*pieceTypeItr == EnEventPieceType::enConversation)
				{
					convIdx = conversationCount;
					conversationCount++;
				}
				else if (*pieceTypeItr == EnEventPieceType::enTrigger)
				{
					triggerIdx = triggerCount;
					triggerCount++;
				}
				else if(*pieceTypeItr == EnEventPieceType::enSet)
				{
					setFuncIdx = setFuncCount;
					setFuncCount++;
					setPieceTmp.emplace_back(piece);
				}

				piece->Init(eventName, *pieceTypeItr, convIdx, triggerIdx, setFuncIdx);
				m_eventPieceArray.emplace_back(piece);

				pieceTypeItr++;
			}

			m_setPieceArray.reserve(setPieceTmp.size());
			for (auto* piece : setPieceTmp)
			{
				m_setPieceArray.emplace_back(piece);
			}

			m_currentPieceIdx = 0;
			m_eventPieceArray.at(m_currentPieceIdx)->StartEvent();

			return;
		}


		void CEventFlow::Release()
		{
			m_eventName.clear();

			for (auto& eventPiece : m_eventPieceArray)
			{
				DeleteGO(eventPiece);
				eventPiece = nullptr;
			}
			m_eventPieceArray.clear();

			m_currentPieceIdx = 0;
			m_pieceTypeListRef = nullptr;
			m_isClear = false;

			return;
		}



	}
}