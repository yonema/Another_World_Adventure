#pragma once
#include "../Quest/QuestData.h"

namespace nsAWA
{
	namespace nsPlayer
	{
		class CPlayerQuestManager
		{
		public:
			/**
			 * @brief 新規クエストを作成
			 * @param questName クエスト名
			 * @param targetEnemyName 討伐目標のモンスター名
			 * @param slayToCompleteNum 完了に必要な討伐数
			*/
			void SetSlayQuest(const std::string& questName, const std::string& targetEnemyName, int slayToCompleteNum);

			/**
			 * @brief クエストを受注中?
			 * @param questName クエスト名
			 * @return 受注中か
			*/
			bool IsQuestReceived(const std::string& questName);

			/**
			 * @brief クエストが完了している?
			 * @param questName クエスト名
			 * @return 完了しているか
			*/
			bool IsQuestCompleted(const std::string& questName);

			/**
			 * @brief クエストを進める
			 * @param slayMonsterName 倒したモンスターの名前
			*/
			void Progress(const std::string& slayMonsterName);

			void EraseQuest(const std::string& eraseQuestName);
		private:
			std::unordered_map < std::string, nsQuest::CQuestData> m_receivingQuests;
		};
	}
}

