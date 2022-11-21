#include "YonemaEnginePreCompile.h"
#include "StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		void CStatusChanger::UpdateAtStart(float deltaTime) {

			//ステータス変化の効果を発動。
			ExecuteAtStart(deltaTime);
		}

		bool CStatusChanger::UpdateAtEnd(float deltaTime) {

			//ステータス変化の効果を発動。
			ExecuteAtEnd(deltaTime);

			//タイマーを更新。
			m_durationTimer -= deltaTime;

			//時間がなくなったら。
			if (m_durationTimer < 0.0f) {

				//自身を破棄。
				delete this;

				//終了したとして知らせる。
				return true;
			}

			//終了しないことを知らせる（まだ効果が残っている）。
			return false;
		}
	}
}
