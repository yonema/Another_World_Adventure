#include "YonemaEnginePreCompile.h"
#include "HitStop.h"
#include "GameActor.h"

namespace nsAWA {

	void CHitStop::Init(IGameActor* target, float hitStopTime) {

		//ターゲットを設定。
		m_target = target;

		//ターゲットのアニメーション速度を保管。
		m_targetAnimationSpeed = m_target->GetModelRenderer()->GetAnimationSpeed();

		//ヒットストップ時間を設定。
		m_timer = hitStopTime;

		//ターゲットをヒットストップ状態に設定。
		m_target->SetHitStop(true);

		//ターゲットのアニメーション速度を0に設定。
		m_target->GetModelRenderer()->SetAnimationSpeed(0.0f);
	}

	void CHitStop::Update(float deltaTime) {

		//タイマーを更新。
		m_timer -= deltaTime;

		//タイマーが0になったら。
		if (m_timer < 0.0f) {

			//ターゲットのヒットストップ状態を解除。
			m_target->SetHitStop(false);

			//ターゲットのアニメーション速度を通常に戻す。
			m_target->GetModelRenderer()->SetAnimationSpeed(m_targetAnimationSpeed);

			//自身を破棄。
			DeleteGO(this);
		}
	}
}