#include "YonemaEnginePreCompile.h"
#include "PlayerAction.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount = 20.0f;		//�ړ���
		}

		void CPlayerAction::Move(float inputX, float inputZ) {

			//�ړ��ʂ��v�Z�B
			auto moveX = inputX * kMoveAmount * m_deltaTimeRef;
			auto moveZ = inputZ * kMoveAmount * m_deltaTimeRef;

			//�ړ��B
			m_position.x += moveX;
			m_position.z += moveZ;
		}
	}
}
