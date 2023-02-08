#include "YonemaEnginePreCompile.h"
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeature::Release() {

			//自身を破棄。
			delete this;
		}

		bool CFeature::Update(float deltaTime) {

			//効果を発動。
			Execute(deltaTime);

			//タイマーを更新。
			m_durationTime -= deltaTime;

			//持続時間が0秒を切ったら。
			if (m_durationTime <= 0.0f) {

				//0秒に設定する。
				m_durationTime = 0.0f;
			}

			//持続時間が0秒になったら。
			if (fabsf(m_durationTime) <= FLT_EPSILON) {

				//死ぬ。
				End();
			}
			
			//まだ生きているかをリターン。
			return IsDead();
		}
	}
}