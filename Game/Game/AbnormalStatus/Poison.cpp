#include "YonemaEnginePreCompile.h"
#include "Poison.h"

namespace nsAWA {

	namespace nsAbnormalStatus {

		namespace {

			constexpr float kPoisonPower = 1.0f;		//毒の強さ（％/s）
			constexpr float kPoisonMaxPower = 100.0f;	//毒の最大の強さ（％/s）
		}

		void CPoison::Init() {

			//ターゲットの最大HPを取得する。
			m_targetMaxHP = m_target->GetStatus()->GetMaxHP();
		}

		void CPoison::Execute(float deltaTime) {

			//毒の威力を計算。
			float damageAmount = m_targetMaxHP * (kPoisonPower / kPoisonMaxPower);

			//与えるダメージ量を計算。
			float poisonPower = damageAmount * deltaTime;

			//ダメージを蓄える。
			//m_damageTank += poisonPower;

			//ターゲットにガード不可のダメージを与える。
			m_target->ApplyDamage(
				poisonPower,
				false			//canGuard
			);
		}
	}
}
