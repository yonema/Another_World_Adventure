#include "YonemaEnginePreCompile.h"
#include "PlayerQuestManager.h"

namespace nsAWA
{
	namespace nsPlayer
	{
		void CPlayerQuestManager::SetSlayQuest(const std::string& questName, const std::string& targetEnemyName, int slayToCompleteNum)
		{
			if (m_receivingQuests.count(questName) >= 1)
			{
				//���łɓ����̃N�G�X�g������B
				return;
			}

			nsQuest::CQuestData newQuestData(questName,targetEnemyName,slayToCompleteNum);

			m_receivingQuests.emplace(std::make_pair(questName, newQuestData));
		}


		bool CPlayerQuestManager::IsQuestReceived(const std::string& questName)
		{
			if (m_receivingQuests.count(questName) == 0)
			{
				//�N�G�X�g���Ȃ�
				return false;
			}

			return true;
		}

		bool CPlayerQuestManager::IsQuestCompleted(const std::string& questName)
		{
			if (m_receivingQuests.count(questName) == 0)
			{
				//�N�G�X�g���Ȃ�
				return false;
			}

			return m_receivingQuests[questName].IsCompleted();
		}

		void CPlayerQuestManager::Progress(const std::string& slayMonsterName)
		{
			for (auto& quests : m_receivingQuests)
			{
				quests.second.Progress(slayMonsterName);
			}
		}

		void CPlayerQuestManager::EraseQuest(const std::string& eraseQuestName)
		{
			if (m_receivingQuests.count(eraseQuestName) == 0)
			{
				//�N�G�X�g���Ȃ�
				return;
			}

			m_receivingQuests.erase(eraseQuestName);
		}

	}
}