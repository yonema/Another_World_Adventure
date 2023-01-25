#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//�A�N�e�B�u�X�L��
		class CActiveSkill : public CSkill
		{
		public:
			void SetUseMP(float useMP) {

				//����MP��ݒ�B
				m_useMP = useMP;
			}

			float GetUseMP() {

				//����MP�����^�[���B
				return m_useMP;
			}
		private:
			float m_useMP = 0.0f;	//����MP
		};
	}
}

