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
			 * @brief �V�K�N�G�X�g���쐬
			 * @param questName �N�G�X�g��
			 * @param targetEnemyName �����ڕW�̃����X�^�[��
			 * @param slayToCompleteNum �����ɕK�v�ȓ�����
			*/
			void SetSlayQuest(const std::string& questName, const std::string& targetEnemyName, int slayToCompleteNum);

			/**
			 * @brief �N�G�X�g���󒍒�?
			 * @param questName �N�G�X�g��
			 * @return �󒍒���
			*/
			bool IsQuestReceived(const std::string& questName);

			/**
			 * @brief �N�G�X�g���������Ă���?
			 * @param questName �N�G�X�g��
			 * @return �������Ă��邩
			*/
			bool IsQuestCompleted(const std::string& questName);

			/**
			 * @brief �N�G�X�g��i�߂�
			 * @param slayMonsterName �|���������X�^�[�̖��O
			*/
			void Progress(const std::string& slayMonsterName);

			void EraseQuest(const std::string& eraseQuestName);
		private:
			std::unordered_map < std::string, nsQuest::CQuestData> m_receivingQuests;
		};
	}
}

