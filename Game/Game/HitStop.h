#pragma once

namespace nsAWA {

	class IGameActor;

	//ヒットストップクラス
	class CHitStop : public IGameObject
	{
	public:
		void Init(IGameActor* target, float hitStopTime);

		void Update(float deltaTime)override final;

	private:
		IGameActor* m_target = nullptr;	//ターゲット
		float m_timer = 0.0f;			//ストップ時間
		float m_targetAnimationSpeed = 0.0f;	//ターゲットのアニメーション速度
	};
}