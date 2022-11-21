#pragma once
#include "AbnormalStatus.h"

namespace nsAWA {

	namespace nsStatusChanger {

		//�ŃN���X
		class CPoison : public CAbnormalStatus
		{
		public:
			void Init()override final;

			void ExecuteAtStart(float deltaTime)override final;

		private:
			float m_targetMaxHP = 0.0f;		//�^�[�Q�b�g�̍ő�HP
			//float m_damageTank = 0.0f;		//�_���[�W�̒~��
		};
	}
}

