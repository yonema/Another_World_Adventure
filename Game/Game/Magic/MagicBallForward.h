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
			int m_createdNum = 0;				//生成した魔法弾の数
			float m_magicIntervalTimer = 0.0f;	//魔法弾の間隔のタイマー
		};
	}
}