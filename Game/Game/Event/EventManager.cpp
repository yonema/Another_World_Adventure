#include "EventManager.h"
#include "EventSetFuncPool.h"
#include "EventNameTable.h"

namespace nsAWA
{
	namespace nsEvent
	{
		const wchar_t* const CEventManager::m_kCsvFilePath = L"Assets/CSV/Event/EventProgress.csv";
		const char* const CEventManager::
			m_kEventCsvPrefixArray[static_cast<int>(EnEventCsvType::enNum)] =
		{
			"NAME",
			"CONDITIONS",
			"PROGRESS",
		};
		const char* const CEventManager::m_kRootEventName = 
			GetEventNameFromTable(EnEventNameType::enGoddesAndAWTransfer);

		const char* const CEventManager::
			m_kEventPiecePrefixArray[static_cast<int>(EnEventPieceType::enNum)] =
		{
			"Set",
			"Trigger",
			"Action",
			"Conversation"
		};
		const char* const CEventManager::m_kLevelFilePath = "Assets/Level3D/EventTriggerLevel.fbx";



		CEventManager* CEventManager::m_instance = nullptr;
		CEventProgressManager* CEventManager::m_progressManagerInstance = nullptr;

		CEventManager::CEventManager()
		{
			Init();

			return;
		}

		CEventManager::~CEventManager()
		{
			Terminate();

			return;
		}

		void CEventManager::Terminate()
		{
			DeleteGO(m_eventSetFuncPool);
			return;
		}




		void CEventManager::Init()
		{
			m_csvManager.LoadCSV(m_kCsvFilePath);

			const auto& allData = m_csvManager.GetCsvData();

			std::unordered_map<std::string, std::list<std::string>> 
				conditionNameToEventMatList = {};

			for (const auto& rowData : allData)
			{
				EnEventCsvType currentType = EnEventCsvType::enNone;
				SEventMaterial eventMaterial = {};

				for (const auto& data : rowData)
				{
					auto checkType = CheckEventCsvType(data);

					if (checkType != EnEventCsvType::enNone)
					{
						currentType = checkType;
						continue;
					}

					switch (currentType)
					{
					case EnEventCsvType::enName:
						eventMaterial.name = data;
						break;
					case EnEventCsvType::enConditions:
						eventMaterial.conditionsEventNameArray.emplace_back(data);
						break;
					case EnEventCsvType::enProgress:
						PushPieceType(&eventMaterial, data);
						break;
					}
				}

				auto itr = m_eventMaterialMap.find(eventMaterial.name);
				if (itr != m_eventMaterialMap.end())
				{
					nsGameWindow::MessageBoxError(L"同じ名前のイベントが複数あります。");
					continue;
				}

				m_eventMaterialMap.emplace(eventMaterial.name, eventMaterial);

				for (const auto& conditionName : eventMaterial.conditionsEventNameArray)
				{
					conditionNameToEventMatList[conditionName].emplace_back(eventMaterial.name);
				}


			}

			m_csvManager.ClearCSV();

			
			for (const auto& eventMatItr : m_eventMaterialMap)
			{
				const auto& eventMat = eventMatItr.second;
				m_eventProgressMap.emplace(
					eventMat.name, 
					CEventProgress(eventMat.name, static_cast<int>(eventMat.pieceTypeList.size()))
				);
			}

			for (auto& eventProgress : m_eventProgressMap)
			{
				auto itr = conditionNameToEventMatList.find(eventProgress.first);
				if (itr == conditionNameToEventMatList.end())
				{
					continue;
				}

				for (const auto& followEventName : itr->second)
				{
					eventProgress.second.AddFollowing(&m_eventProgressMap.at(followEventName));
				}				
			}

			auto itr = m_eventProgressMap.find(m_kRootEventName);
			if (itr == m_eventProgressMap.end())
			{
				int a = 1;
			}
			m_progressManagerInstance->AddRootEvent(&m_eventProgressMap.at(m_kRootEventName));



			InitEventTriggerTRS();

			m_eventSetFuncPool = NewGO<CEventSetFuncPool>();

			return;
		}


		CEventManager::EnEventCsvType CEventManager::CheckEventCsvType(const std::string& data)
		{
			int idx = 0;
			EnEventCsvType type = EnEventCsvType::enNone;

			for (; idx < static_cast<int>(EnEventCsvType::enNum); idx++)
			{
				if (data == m_kEventCsvPrefixArray[idx])
				{
					type = static_cast<EnEventCsvType>(idx);
					break;
				}
			}			

			return type;
		}


		void CEventManager::PushPieceType(SEventMaterial* eventMatOut, const std::string& data)
		{
			int idx = 0;

			for (int i = 0; i < static_cast<int>(EnEventPieceType::enNum); idx++)
			{
				if (data == m_kEventPiecePrefixArray[idx])
				{
					break;
				}
			}

			if (idx >= static_cast<int>(EnEventPieceType::enNum))
			{
				nsGameWindow::MessageBoxError(L"EventPieceTypeエラー");
			}

			eventMatOut->pieceTypeList.emplace_back(static_cast<EnEventPieceType>(idx));


			return;
		}


		void CEventManager::InitEventTriggerTRS()
		{
			CLevel3D level3D;

			level3D.Init(
				m_kLevelFilePath,
				[&](const SLevelChipData& chipData)->bool
				{
					if (chipData.ForwardMatchName("EventTrigger_"))
					{
						const char* name = chipData.name.c_str();
						name += strlen("EventTrigger_");
						PushEventTrigger(
							name, STRS(chipData.position, chipData.rotation, chipData.scale));
					}

					return true;
				});


			return;
		}



		void CEventManager::PushEventTrigger(const std::string& name, const STRS& trs)
		{

			auto pair = nsUtils::SplitString(name.c_str(), '_');

			auto& engName = pair.first;
			auto& num = pair.second;

			auto engToJpItr = g_kEventNameEngToJpMap.find(engName);

			if (engToJpItr == g_kEventNameEngToJpMap.end())
			{
				nsGameWindow::MessageBoxError(L"イベント名を英語から日本語に変換するマップに登録されていません。");
				return;
			}

			const char* jpName = engToJpItr->second;
			std::string finalName = jpName;
			finalName += num;

			auto triggerItr = m_eventTriggerMap.find(finalName);

			if (triggerItr != m_eventTriggerMap.end())
			{
				nsGameWindow::MessageBoxError(L"同じ名前のイベントトリガーがレベルに設定されています。");
				return;
			}

			m_eventTriggerMap.emplace(finalName, trs);

			return;
		}





	}
}