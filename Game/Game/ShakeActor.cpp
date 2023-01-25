#include "YonemaEnginePreCompile.h"
#include "ShakeActor.h"
#include "GameActor.h"

namespace nsAWA {

	namespace {

		constexpr float kShakeMinAmount = 0.8f;	//揺れ幅の最低
		constexpr float kShakeValue = 8.0f;	//揺れの大きさ
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
		m_shakeTime -= deltaTime;

		if (m_shakeTime < FLT_EPSILON) {

			//座標を元に戻す。
			m_shakeActor->SetPosition(m_actorOldPosition);

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
		CVector3 shakeVector = CVector3::Zero();
		nsUtils::CRandom random;
		shakeVector.x = random.GetRangeFloat(shakeMin, shakeMax);
		shakeVector.y = random.GetRangeFloat(shakeMin, shakeMax);
		shakeVector.z = random.GetRangeFloat(shakeMin, shakeMax);

		//座標を設定。
		m_shakeActor->SetPosition(m_actorOldPosition + shakeVector);
	}
}