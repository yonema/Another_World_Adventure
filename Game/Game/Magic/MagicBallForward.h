#pragma once
#include "MagicBase.h"

namespace nsAWA{

	namespace nsMagic {

		class CMagicBallForward : public CMagicBase
		{
		public:
			bool Start()override final;

			void Update(float deltaTime)override final;

		private:
			void CreateMagicBall();

		private:
			int m_createdNum = 0;				//�����������@�e�̐�
			float m_magicIntervalTimer = 0.0f;	//���@�e�̊Ԋu�̃^�C�}�[
		};
	}
}