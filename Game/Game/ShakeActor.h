#pragma once

namespace nsAWA {

	//�O���錾
	class IGameActor;

	//�A�N�^�[��h�炷�N���X
	class CShakeActor : public IGameObject
	{
	public:
		void Init(IGameActor* shakeActor, float shakeTime);

		void Update(float deltaTime)override final;

	private:
		IGameActor* m_shakeActor = nullptr;	//�h�炷�A�N�^�[
		float m_shakeTime = 0.0f;				//�h��̎���
		CVector3 m_actorOldPosition = CVector3::Zero();	//�A�N�^�[�̌����W
	};
}


