#include "YonemaEnginePreCompile.h"
#include "ShakeActor.h"
#include "GameActor.h"

namespace nsAWA {

	namespace {

		constexpr float kShakeMinAmount = -1.0f;	//揺れ幅の最低
		constexpr float kShakeValue = 6.0f;	//揺れの大きさ
	}

	void CShakeActor::Init(IGameActor* shakeActor, float shakeTime) {

		//初期化。
		m_shakeActor = shakeActor;
		m_shakeTime = shakeTime;

		//アクターの元座標を取得。
		m_actorOldPosition = m_shakeActor->GetPosition();
	}

	void CShakeActor::Update(float deltaTime) {

		//揺れ時間を更新。
		m_shakeTime -= deltaTime * 0.4f;

		if (m_shakeTime < FLT_EPSILON) {

			//オフセットを元に戻す。
			m_shakeActor->SetPositionOffset(CVector3::Zero());

			//この機能を破棄。
			DeleteGO(this);

			//終了。
			return;
		}

		//揺れ幅を求める。
		float shakeAmount = m_shakeTime * kShakeValue;

		//揺れ幅の最低値と最大値を求める。
		float shakeMax = shakeAmount;
		float shakeMin = shakeMax * kShakeMinAmount;

		//揺れ幅を設定。
		m_shakeVector.x = Random()->GetRangeFloat(shakeMin, shakeMax);
		m_shakeVector.y = Random()->GetRangeFloat(shakeMin, shakeMax);
		m_shakeVector.z = Random()->GetRangeFloat(shakeMin, shakeMax);

		//座標を設定。
		m_shakeActor->SetPositionOffset(m_shakeVector);
	}
}