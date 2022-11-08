#include "YonemaEnginePreCompile.h"
#include "PlayerAction.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount = 20.0f;		//移動量
		}

		void CPlayerAction::Move(float inputX, float inputZ) {

			//移動量を計算。
			auto moveX = inputX * kMoveAmount * m_deltaTimeRef;
			auto moveZ = inputZ * kMoveAmount * m_deltaTimeRef;

			//移動。
			m_position.x += moveX;
			m_position.z += moveZ;
		}
	}
}
