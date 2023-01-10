#pragma once
#include "../GameActorCollider.h"

namespace nsAWA {

	//�O���錾
	namespace nsMonster {

		class CMonster;
	}

	namespace nsMonster {

		//�����X�^�[�����蔻��N���X
		class CMonsterCollider : public CGameActorCollider
		{
		public:
			void CreateCollider();

			void Update();

			void Release();

		public:
			CMonster* GetGameActor() {

				//�����X�^�[�̃|�C���^�����^�[���B
				return m_monster;
			}
		private:
			CPhysicsTriggerObject m_triggerBox;		//�����蔻��
			const CVector3* m_position = nullptr;	//���W
			CMonster* m_monster = nullptr;			//�����X�^�[�̃|�C���^
		};
	}
}