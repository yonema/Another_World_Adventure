#include "YonemaEnginePreCompile.h"
#include "PlayerAction.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount = 20.0f;		//ˆÚ“®—Ê
		}

		void CPlayerAction::Move(float inputX, float inputZ) {

			//ˆÚ“®—Ê‚ğŒvZB
			auto moveX = inputX * kMoveAmount * m_deltaTimeRef;
			auto moveZ = inputZ * kMoveAmount * m_deltaTimeRef;

			//ˆÚ“®B
			m_position.x += moveX;
			m_position.z += moveZ;
		}
	}
}
