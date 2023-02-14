#pragma once

namespace nsAWA
{
	namespace nsPlayer
	{
		class CPlayerQuestManager
		{
		public:
			/**
			 * @brief �N�G�X�g���Z�b�g����
			 * @param slayToCompleteNum �N���A���邽�߂̓�����
			*/
			void SetSlayQuest(int slayToCompleteNum)
			{
				m_slayProgressNum = 0;
				m_slayToCompleteNum = slayToCompleteNum;

				m_isQuestReceived = true;
			}

			/**
			 * @brief �N�G�X�g���󂯂Ă���?
			 * @return 
			*/
			bool IsQuestReceived()
			{
				return m_isQuestReceived;
			}

			/**
			 * @brief �N�G�X�g�̊��������𖞂����Ă���?
			 * @return �������������ɕK�v�Ȑ��ȏォ?
			*/
			bool IsQuestCompleted()
			{
				return m_slayProgressNum >= m_slayToCompleteNum;
			}

			/**
			 * @brief ��������i�߂�
			*/
			void Progress(const std::string& slayMonsterName)
			{
				//TODO:���O����N�G�X�g����
				m_slayProgressNum++;
			}

			/**
			 * @brief �N�G�X�g�����Z�b�g����
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

