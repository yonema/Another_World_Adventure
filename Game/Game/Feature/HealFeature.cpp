#include "YonemaEnginePreCompile.h"
#include "HealFeature.h"
#include "../GameActor.h"

namespace nsAWA {

	namespace nsFeature {

		void HealFeature::Init(IGameActor* target, EnHealTarget healTarget, float healValue) {

			//情報を設定。
			m_target = target;
			m_healTarget = healTarget;
			m_healValue = healValue;
		}

		void HealFeature::Create() {

			switch (m_healTarget) {

				//HP回復。
			case EnHealTarget::enHP:
				m_target->HealHP(m_healValue);
				break;

				//MP回復。
			case EnHealTarget::enMP:
				m_target->HealMP(m_healValue);
				break;

				//SP回復。
			case EnHealTarget::enSP:
				m_target->HealSP(m_healValue);
				break;
			}
		}
	}
}