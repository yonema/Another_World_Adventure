#include "YonemaEnginePreCompile.h"
#include "EventProgressManager.h"
#include "EventProgress.h"


namespace nsAWA
{
	namespace nsEvent
	{
		void CEventProgressManager::ProgressEvent(std::string eventName)
		{
			for (auto event : m_latestEvents)
			{
				//名前が一致しないならスキップ
				if (event->GetName() != eventName)
				{
					continue;
				}

				//一致したイベントを進める
				event->Progress();

				//イベントが完全に終わっていないなら終了
				if (event->IsClear() == false)
				{
					return;
				}

				//イベントをコンプリートしている

				//コンプリートしたイベントを前提条件とするイベントを追加
				std::list<CEventProgress*> childEvents = event->GetChildren();

				for (CEventProgress* childEvent : childEvents)
				{
					//クリアしたイベントを前提条件とするイベントにクリアした事を通知し参照カウントを下げる
					childEvent->ClearPremise();

					//追加する予定のイベントがすでに追加されているかチェック()
					bool found = false;
					auto itr = m_latestEvents.begin();
					for (auto itr = m_latestEvents.begin();itr != m_latestEvents.end();itr++)
					{
						if ((*itr) == childEvent)
						{
							found = true;
							break;
						}
					}

					if (found == false)
					{
						m_latestEvents.emplace_back(childEvent);
					}
				}

				m_latestEvents.remove(event);
				return;
			}

			//実行不可能なイベントなので何もしていない。
			return;
		}

		int CEventProgressManager::GetProgression(std::string eventName)
		{
			for (auto event : m_latestEvents)
			{
				if (eventName != event->GetName())
				{
					continue;
				}

				return event->GetProgression();
			}

			return -1;
		}
	}
}