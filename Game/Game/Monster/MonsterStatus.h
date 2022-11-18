#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsMonster {

		//モンスターステータス
		class CMonsterStatus : public CStatus
		{
		public:
			float GetMaxHP()const {

				return m_maxMP;
			}

		private:
			float m_maxMP = 0;
		};
	}
}

