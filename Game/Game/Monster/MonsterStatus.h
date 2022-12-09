#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsMonster {

		//モンスターステータス
		class CMonsterStatus : public CStatus
		{
		public:
			float GetHP()const {

				return m_HP;
			}
			float GetMaxHP()const {

				return m_maxHP;
			}
			float GetMP()const {

				return m_MP;
			}
			float GetMaxMP()const {

				return m_maxMP;
			}
			float GetSP()const {

				return m_SP;
			}
			float GetMaxSP()const {

				return m_maxSP;
			}

		private:
			float m_HP = 0.0f;
			float m_maxHP = 0.0f;
			float m_MP = 0.0f;
			float m_maxMP = 0.0f;
			float m_SP = 0.0f;
			float m_maxSP = 0.0f;
		};
	}
}

