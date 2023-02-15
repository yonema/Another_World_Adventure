#include "YonemaEnginePreCompile.h"
#include "EventProgressManager.h"
#include "EventProgress.h"


namespace nsAWA
{
	namespace nsEvent
	{
		CEventProgressManager* CEventProgressManager::m_instance = nullptr;

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

				//イベントがまだ進行中、またはすでに終了済みなら何もしない
				if (event->GetProgressState() != EnEventState::enCompleted)
				{
					return;
				}

				//イベントをコンプリートしている

				//イベントを終了済みとしてマーク
				event->MarkAsExpired();

				//クリアしたイベントリストにイベント名を追加
				m_cleardEventNameList.emplace_back(event->GetName());

				//コンプリートしたイベントを前提条件とするイベントを追加
				std::list<CEventProgress*> childEvents = event->GetChildren();

				for (CEventProgress* childEvent : childEvents)
				{
					//クリアしたイベントを前提条件とするイベントにクリアした事を通知し参照カウントを下げる
					childEvent->ClearPremise();

					//追加する予定のイベントがすでに追加されているかチェック
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

					//追加されていないので新たに追加
					if (found == false)
					{
						m_latestEvents.emplace_back(childEvent);
					}
				}
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

				//名前に一致するイベントが見つかったら、その進行度を返す
				return event->GetProgression();
			}

			return -1;
		}

		EnEventState CEventProgressManager::GetProgressState(std::string eventName)
		{
			for (auto event : m_latestEvents)
			{
				if (eventName != event->GetName())
				{
					continue;
				}

				//名前に一致するイベントが見つかったら、その進行度を返す
				return event->GetProgressState();
			}

			return EnEventState::enNotReady;
		}

		void CEventProgressManager::SetClearedEvents(std::vector<std::string> clearedEventNameList)
		{
			for (auto clearedEventName : clearedEventNameList)
			{
				for (auto event : m_latestEvents)
				{
					//名前が一致しないならスキップ
					if (event->GetName() != clearedEventName)
					{
						continue;
					}

					//一致したイベントを終了済みとしてマーク
					event->MarkAsExpired();

					//クリアしたイベントなので進行度はマックスにしておく
					event->SetProgression(event->GetMaxProgress());

					//クリアしたイベントリストにイベント名を追加
					m_cleardEventNameList.emplace_back(event->GetName());

					//コンプリートしたイベントを前提条件とするイベントを追加
					std::list<CEventProgress*> childEvents = event->GetChildren();

					for (CEventProgress* childEvent : childEvents)
					{
						//クリアしたイベントを前提条件とするイベントにクリアした事を通知し参照カウントを下げる
						childEvent->ClearPremise();

						//追加する予定のイベントがすでに追加されているかチェック
						bool found = false;
						auto itr = m_latestEvents.begin();
						for (auto itr = m_latestEvents.begin(); itr != m_latestEvents.end(); itr++)
						{
							if ((*itr) == childEvent)
							{
								found = true;
								break;
							}
						}

						//追加されていないので新たに追加
						if (found == false)
						{
							m_latestEvents.emplace_back(childEvent);
						}
					}
					
					break;
				}
			}
		}


		std::vector<std::string> CEventProgressManager::GetProgressionList()
		{
			std::vector<std::string> progressionList;

			//進行中のイベントの進行度だけ格納
			for (auto progressionEvent : m_latestEvents)
			{
				if (progressionEvent->GetProgressState() == EnEventState::enProgress)
				{
					char str[256];

					int progression = 0;
					
					//TODO:現在はイベントの進行度が復元できていないようなので一旦すべて進行度0とする
					//int progression = progressionEvent->GetProgression();

					sprintf_s(str, sizeof(str), "%d", progression);

					std::string progressionString = str;

					progressionList.emplace_back(progressionString);
				}
			}

			return progressionList;
		}

		void CEventProgressManager::SetProgressionList(std::vector<std::string> progressionList)
		{
			int count = 0;

			for (auto latestEvent : m_latestEvents)
			{
				if (latestEvent->GetProgressState() != EnEventState::enProgress)
				{
					continue;
				}

				int progression = atoi(progressionList[count].c_str());

				latestEvent->SetProgression(progression);

				count++;
			}
		}
	}
}