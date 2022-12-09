#pragma once
#include "../GameActorCollider.h"

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsPlayer {

		//�v���C���[�̓����蔻��N���X
		class CPlayerCollider : public CGameActorCollider
		{
		public:
			void CreateCollider();

			void Update();

			void Release();

		public:
			CPlayer* GetPlayer() {

				//�v���C���[�̃|�C���^�����^�[���B
				return m_player;
			}

		private:
			CPhysicsTriggerObject m_triggerBox;		//�����蔻��
			const CVector3* m_position = nullptr;	//���W

			CPlayer* m_player = nullptr;	//�v���C���[�̃|�C���^
		};
	}
}