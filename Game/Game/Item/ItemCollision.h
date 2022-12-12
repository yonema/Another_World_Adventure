#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsItem {

		//�A�C�e�����̃N���X
		class CItemCollision : nsUtils::SNoncopyable
		{
		public:
			void Init(const CVector3& position);

			void Release();

			void Throw(const CVector3& throwDirection);

			void DeactivateCollision() {

				//���̂ƃg���K�[���A�N�e�B�u�ɂ���B
				m_rigidBody.Deactivate();
				m_trigger.Deactivate();
			}

			void Update(float deltaTime);

		private:
			void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

			void OnFeatureTriggerEnter(CExtendedDataForRigidActor* otherData);

		public:

			CVector3 GetPosition()const {

				//���̂̍��W���擾�B
				return m_rigidBody.GetPosition();
			}

			bool IsHit()const {

				//�����ɓ����������ǂ����B
				return m_isHit;
			}

			bool IsEnd()const {

				//�S�ďI���������B
				return m_isEnd;
			}

			std::list<IGameActor*>* GetHitActorList() {

				//�����蔻��ɓ������A�N�^�[�̃��X�g�����^�[���B
				return &m_hitActorList;
			}
		private:
			CPhysicsDynamicObject m_rigidBody;				//����
			CPhysicsTriggerObject m_trigger;				//�g���K�[
			CPhysicsTriggerObject m_featureTrigger;			//���ʂ�t�^����͈͂̃g���K�[
			bool m_isHit = false;		//�����ɓ���������
			bool m_isEnd = false;		//���ׂďI��������
			std::list<IGameActor*> m_hitActorList;		//�����蔻��ɓ������A�N�^�[�̃��X�g
			float m_executeTriggerTimer = 0.0f;		//���ʔ͈̓g���K�[�̃^�C�}�[
		};
	}
}