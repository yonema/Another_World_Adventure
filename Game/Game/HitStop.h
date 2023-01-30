#pragma once

namespace nsAWA {

	class IGameActor;

	//�q�b�g�X�g�b�v�N���X
	class CHitStop : public IGameObject
	{
	public:
		void Init(IGameActor* target, float hitStopTime);

		void Update(float deltaTime)override final;

	private:
		IGameActor* m_target = nullptr;	//�^�[�Q�b�g
		float m_timer = 0.0f;			//�X�g�b�v����
		float m_targetAnimationSpeed = 0.0f;	//�^�[�Q�b�g�̃A�j���[�V�������x
	};
}