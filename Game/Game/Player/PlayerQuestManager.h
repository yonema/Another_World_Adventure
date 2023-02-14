#pragma once

namespace nsAWA
{
	namespace nsPlayer
	{
		class CPlayerQuestManager
		{
		public:
			/**
			 * @brief クエストをセットする
			 * @param slayToCompleteNum クリアするための討伐数
			*/
			void SetSlayQuest(int slayToCompleteNum)
			{
				m_slayProgressNum = 0;
				m_slayToCompleteNum = slayToCompleteNum;

				m_isQuestReceived = true;
			}

			/**
			 * @brief クエストを受けている?
			 * @return 
			*/
			bool IsQuestReceived()
			{
				return m_isQuestReceived;
			}

			/**
			 * @brief クエストの完了条件を満たしている?
			 * @return 討伐数が完了に必要な数以上か?
			*/
			bool IsQuestCompleted()
			{
				return m_slayProgressNum >= m_slayToCompleteNum;
			}

			/**
			 * @brief 討伐数を進める
			*/
			void Progress(const std::string& slayMonsterName)
			{
				//TODO:名前からクエスト検索
				m_slayProgressNum++;
			}

			/**
			 * @brief クエストをリセットする
			*/
			void Reset()
			{
				m_isQuestReceived = false;
				m_slayProgressNum = 0;
				m_slayToCompleteNum = 0;
			}
		private:
			bool m_isQuestReceived = false;

			int m_slayProgressNum = 0;

			int m_slayToCompleteNum = 0;
		};
	}
}

