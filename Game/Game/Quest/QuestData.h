#pragma once

namespace nsAWA
{
	namespace nsQuest
	{
		class CQuestData
		{
		public:
			CQuestData() = default;

			CQuestData(const std::string& questName,const std::string& targetEnemyName,int slayToCompleteNum)
				:m_questName(questName),m_targetEnemyName(targetEnemyName),m_slayToCompleteNum(slayToCompleteNum) {}
		
			void Progress(std::string slayedEnemyName);

			bool IsCompleted()
			{
				return m_isComplete;
			}

		private:
			void CalcComplete()
			{
				m_isComplete = m_slayProgressNum >= m_slayToCompleteNum;
			}

		private:
			std::string m_questName = "";

			std::string m_targetEnemyName = "";

			int m_slayProgressNum = 0;		//Œ»İ‚Ì“¢”°”
			
			int m_slayToCompleteNum = 0;	//Š®—¹‚É•K—v‚È“¢”°”

			bool m_isComplete = false;
		};
	}
}

