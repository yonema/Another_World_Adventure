#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//アクティブスキル
		class CActiveSkill : public CSkill
		{
		public:
			void SetUseMP(float useMP) {

				//消費MPを設定。
				m_useMP = useMP;
			}

			float GetUseMP() {

				//消費MPをリターン。
				return m_useMP;
			}
		private:
			float m_useMP = 0.0f;	//消費MP
		};
	}
}

