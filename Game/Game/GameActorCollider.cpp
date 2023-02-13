#include "YonemaEnginePreCompile.h"
#include "GameActorCollider.h"

namespace nsAWA {

	void CGameActorCollider::Release() {

		//„‘Ì‚ğ”jŠüB
		m_rigidBody.Release();

		//ƒgƒŠƒK[‚ğ”jŠüB
		m_trigger.Release();
	}
}