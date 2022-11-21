#pragma once
#include "AbnormalStatus.h"

namespace nsAWA {

	namespace nsStatusChanger {

		//毒クラス
		class CPoison : public CAbnormalStatus
		{
		public:
			void Init()override final;

			void ExecuteAtStart(float deltaTime)override final;

		private:
			float m_targetMaxHP = 0.0f;		//ターゲットの最大HP
			//float m_damageTank = 0.0f;		//ダメージの蓄え
		};
	}
}

