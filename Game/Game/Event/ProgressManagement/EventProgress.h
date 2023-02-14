#pragma once

namespace nsAWA
{
	namespace nsEvent
	{
		enum class EnEventState
		{
			enNotReady,	//進行不可
			enProgress,	//進行中
			enCompleted,//完了
			enExpired,	//終了済み
		};

		class CEventProgress
		{
		public:
			/**
			 * @brief コンストラクタ
			 * @param name イベント名
			 * @param maxProgress 最大進行度
			*/
			CEventProgress(std::string name, int maxProgress)
			{
				m_eventName = name;
				m_maxProgress = maxProgress;
			}

			/**
			 * @brief このイベントを前提条件とするイベントを追加する
			 * @param event 追加するイベント
			 * @return 追加したイベントのポインタ(メソッドチェインとして使用可能)
			*/
			CEventProgress* AddFollowing(CEventProgress* event)
			{

				m_followingEvents.emplace_back(event);

				event->AddPremise();

				return event;
			}

			/**
			 * @brief イベントの進行度を進める
			*/
			void Progress()
			{
				if (m_progression >= m_maxProgress)
				{
					return;
				}

				m_progression++;

				if (m_progression == m_maxProgress)
				{
					m_eventState = EnEventState::enCompleted;
				}
			}

			/**
			 * @brief このイベントの前提条件となっているイベントの数を加算する
			*/
			void AddPremise()
			{
				m_referenceCount++;
			}

			/**
			 * @brief このイベントの前提条件となっているイベントの数を減算する(前提イベントがクリアされた時に呼ばれる)
			*/
			void ClearPremise()
			{
				m_referenceCount--;
			}

			/**
			 * @brief このイベントは今実行可能か?
			 * @return イベントが実行可能か(終了していない前提条件イベントがなければ実行可能)
			*/
			bool IsExecutable()
			{
				return m_referenceCount == 0;
			}

			/**
			 * @brief このイベントを前提条件とするイベントのリストを取得
			 * @return イベントのリスト
			*/
			const std::list<CEventProgress*>& GetChildren()
			{
				return m_followingEvents;
			}

			/**
			 * @brief イベントをすべてクリアした?
			 * @return イベントの進行度が最大進行度と一緒ならクリア
			*/
			bool IsClear()
			{
				return m_progression == m_maxProgress;
			}

			/**
			 * @brief イベント名を取得
			 * @return イベント名
			*/
			std::string GetName()
			{
				return m_eventName;
			}

			/**
			 * @brief イベントの進行度を取得
			 * @return イベントの進行度
			*/
			int GetProgression()
			{
				return m_progression;
			}

			/**
			 * @brief イベントの進行状態を取得
			 * @return イベントの進行状態
			*/
			EnEventState GetProgressState()
			{
				return m_eventState;
			}

			/**
			 * @brief イベントを終了済みとしてマーク
			*/
			void MarkAsExpired()
			{
				m_eventState = EnEventState::enExpired;
			}

			constexpr int GetMaxProgress() const noexcept
			{
				return m_maxProgress;
			}
		private:
			std::list<CEventProgress*> m_followingEvents;	//このイベントを前提条件とするイベント

			int m_referenceCount = 0;						//このイベントの前提条件になるイベントの数

			int m_progression = 0;							//進行度

			int m_maxProgress = 0;							//最大進行度

			std::string m_eventName = "";					//イベント名

			EnEventState m_eventState = EnEventState::enProgress;	//イベントの進行状態

		};
	}
}

