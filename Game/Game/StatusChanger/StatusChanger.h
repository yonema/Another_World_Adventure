#pragma once
#include "../GameActor.h"

namespace nsAWA {

	namespace nsStatusChanger {

		class CStatusChanger : nsUtils::SNoncopyable
		{
		public:
			
			/**
			 * @brief �߂�l�ł͂��̃X�e�[�^�X�ω����I����������Ԃ��B
			*/
			bool Update(float deltaTime);

		protected:
			virtual void Execute(float deltaTime) = 0;

		protected:
			float m_durationTimer = 0.0f;		//��������
			IGameActor* m_target = nullptr;		//���ʂ������炷�^�[�Q�b�g
		};
	}
}

