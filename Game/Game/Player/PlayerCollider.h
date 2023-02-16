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

		public:
			CPlayer* GetPlayer() {

				//�v���C���[�̃|�C���^�����^�[���B
				return m_player;
			}

			bool IsReleased()const {

				//�j�����ꂽ���ǂ��������^�[���B
				return m_released;
			}

		private:
			bool m_released = false;				//�j�����ꂽ�H
			const CVector3* m_position = nullptr;	//���W

			CPlayer* m_player = nullptr;	//�v���C���[�̃|�C���^
		};
	}
}