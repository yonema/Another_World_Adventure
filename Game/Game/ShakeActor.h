#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;

	//アクターを揺らすクラス
	class CShakeActor : public IGameObject
	{
	public:
		void Init(IGameActor* shakeActor, float shakeTime);

		void Update(float deltaTime)override final;

	private:
		IGameActor* m_shakeActor = nullptr;	//揺らすアクター
		float m_shakeTime = 0.0f;				//揺れの時間
		CVector3 m_actorOldPosition = CVector3::Zero();	//アクターの元座標
	};
}


