#pragma once

namespace nsAWA {

	class IGameActor;

	//�Q�[���A�N�^�[�̓����蔻��N���X
	class CGameActorCollider : nsUtils::SNoncopyable
	{
	public:
		void Init(IGameActor* gameActor) {

			//�e�̃Q�[���A�N�^�[��ݒ�B
			m_gameActor = gameActor;

			//�����蔻��𐶐��B
			CreateCollider();
		}
		virtual void CreateCollider() = 0;

		void Release();

	public:

		IGameActor* GetGameActor()const {

			//�e�̃Q�[���A�N�^�[���擾�B
			return m_gameActor;
		}

		const CPhysicsTriggerObject* GetTrigger()const {

			//�g���K�[���擾�B
			return &m_trigger;
		}
	private:
		CPhysicsDynamicObject m_rigidBody;				//����
		CPhysicsTriggerObject m_trigger;				//�g���K�[
	protected:
		IGameActor* m_gameActor = nullptr;				//�e�̃Q�[���A�N�^�[
	};
}