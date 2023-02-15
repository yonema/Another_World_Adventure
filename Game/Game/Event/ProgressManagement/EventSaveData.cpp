#include "YonemaEnginePreCompile.h"
#include "EventSaveData.h"
#include "EventProgressManager.h"
#include "../../CSV/CSVManager.h"


namespace nsAWA
{
	namespace nsEvent
	{
		void CEventSaveData::Save()
		{
			//データ情報を破棄。
			m_eventSaveData.clear();

			CEventProgressManager* eventManager = nsEvent::CEventProgressManager::CreateInstance();

			//イベントのクリア状況をセーブ
			SaveClearedEventData(eventManager);

			//進行中のイベントの進行度をセーブ
			SaveEventProgressionData(eventManager);

			//データを保存。
			nsCSV::CCsvManager csvManager;
			csvManager.SaveCSV(kEventDataCSVFilePath, m_eventSaveData);
		}

		void CEventSaveData::Load()
		{
			//現在格納されているデータがあれば破棄
			m_eventSaveData.clear();

			//イベントデータ格納用のCSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kEventDataCSVFilePath);

			//データのイテレータを取得。
			auto data = csvManager.GetCsvData();
			auto itr = data.begin();

			nsEvent::CEventProgressManager* eventManager = nsEvent::CEventProgressManager::CreateInstance();
			//クリアしたクエストをロード
			eventManager->SetClearedEvents(*itr);
			itr++;

			//進行中のクエストの進行度をロード
			eventManager->SetProgressionList(*itr);
		}

		void CEventSaveData::SaveClearedEventData(CEventProgressManager* eventManager)
		{
			m_eventSaveData.emplace_back(eventManager->GetClearedEvents());
		}

		void CEventSaveData::SaveEventProgressionData(CEventProgressManager* eventManager)
		{
			m_eventSaveData.emplace_back(eventManager->GetProgressionList());
		}
	}
}