#pragma once
#include "EventProgress.h"

namespace nsAWA
{
	namespace nsEvent
	{
		class CEventProgressManager : nsUtils::SNoncopyable
		{
		private:
			CEventProgressManager(){}
			~CEventProgressManager(){}

		public:
			/**
			 * @brief インスタンスを作成
			 * @return インスタンス
			*/
			static inline CEventProgressManager* CreateInstance() noexcept
			{
				if (m_instance == nullptr)
				{
					m_instance = new CEventProgressManager();
				}
				return m_instance;
			}

			/**
			 * @brief インスタンスを取得
			 * @return インスタンス
			*/
			static inline CEventProgressManager* GetInstance() noexcept
			{
				return m_instance;
			}

			/**
			 * @brief インスタンスを削除
			 * @return 
			*/
			static void DeleteInstance() noexcept
			{
				if (m_instance == nullptr)
				{
					return;
				}
				delete m_instance;
				m_instance = nullptr;
			}

			/**
			 * @brief ルートイベントを追加
			 * @param event ルートに追加するイベント
			 * @return 追加したイベントのポインタ(メソッドチェインとして使用可能)
			*/
			CEventProgress* AddRootEvent(CEventProgress* event)
			{
				m_latestEvents.emplace_back(event);

				return event;
			}

			/**
			 * @brief 名前で指定したイベントの進行度を進める
			 * @param eventName 進めるイベント名
			*/
			void ProgressEvent(std::string eventName);

			/**
			 * @brief 名前で指定したイベントの進行度を取得する
			 * @param eventName 取得するイベント名
			 * @return イベントの進行度(進行できない状態なら-1)
			*/
			int GetProgression(std::string eventName);

			/**
			 * @brief 名前で指定したイベントの進行状態を取得する
			 * @param eventName 取得するイベント名
			 * @return イベントの進行状態
			*/
			EnEventState GetProgressState(std::string eventName);


			constexpr const auto& GetLatestEvents() const noexcept
			{
				return m_latestEvents;
			}

			std::vector<std::string> GetProgressionList();
		private:
			static CEventProgressManager* m_instance;		//インスタンス
			
			std::list<CEventProgress*> m_latestEvents;		//進行度をチェックするイベント(前提条件によって実行できない物も含む)
		
			std::vector<std::string> m_cleardEventNameList;	//クリアしたイベントのリスト(クリアした順に格納)

			std::vector<std::string> m_progressionList;		//クリアしていないイベントのうち進行中のものの進行度のリスト
		};
	}
}
