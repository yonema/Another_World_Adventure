#pragma once
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"

namespace nsAWA {

	namespace nsWeapon {

		class CWeapon;
	}

	namespace nsPlayer {

		//�v���C���[�N���X
		class CPlayer : public IGameObject
		{
		public:
			static const char* const m_kObjName_Player;		//�v���C���[�N���X�̖��O
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void ApplyDamage(int power);

		public:
			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_action.GetPosition();
			}

			const CQuaternion& GetRotation()const {

				//��]�����擾�B
				return m_action.GetRotation();
			}

			CPlayerStatus* GetStatus() {

				//�X�e�[�^�X���󂯎��B
				return &m_status;
			}
		private:
			void CreatePlayerModel();

			void CreateWeapon();
		private:
			CModelRenderer* m_modelRenderer = nullptr;	//�v���C���[���f��
			CPlayerInput m_input;						//����
			CPlayerAction m_action;						//�A�N�V����
			CPlayerStatus m_status;						//�X�e�[�^�X
			nsWeapon::CWeapon* m_weapon = nullptr;		//����
		};
	}
}

