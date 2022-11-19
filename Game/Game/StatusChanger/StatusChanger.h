#pragma once
#include "../GameActor.h"

namespace nsAWA {

	namespace nsStatusChanger {

		class CStatusChanger : nsUtils::SNoncopyable
		{
		public:
			
			/**
			 * @brief 戻り値ではこのステータス変化が終了したかを返す。
			*/
			bool Update(float deltaTime);

		protected:
			virtual void Execute(float deltaTime) = 0;

		protected:
			float m_durationTimer = 0.0f;		//持続時間
			IGameActor* m_target = nullptr;		//効果をもたらすターゲット
		};
	}
}

