#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsMonster {

		//�����X�^�[�X�e�[�^�X
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

