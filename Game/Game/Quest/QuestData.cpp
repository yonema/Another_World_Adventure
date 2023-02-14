#include "YonemaEnginePreCompile.h"
#include "QuestData.h"
#include "../GameLog/GameLog.h"

namespace nsAWA
{
	namespace nsQuest
	{
		void CQuestData::Progress(std::string slayedEnemyName)
		{
			if (slayedEnemyName != m_targetEnemyName || m_isComplete == true)
			{
				return;
			}

			m_slayProgressNum++;

			CalcComplete();

			if (IsCompleted())
			{
				nsGameLog::CGameLog::GetInstance()->AddGameLog(m_questName + "をコンプリート!");
			}
		}
	}
}