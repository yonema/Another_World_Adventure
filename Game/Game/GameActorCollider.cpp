#include "YonemaEnginePreCompile.h"
#include "GameActorCollider.h"

namespace nsAWA {

	void CGameActorCollider::Release() {

		//���̂�j���B
		m_rigidBody.Release();

		//�g���K�[��j���B
		m_trigger.Release();
	}
}