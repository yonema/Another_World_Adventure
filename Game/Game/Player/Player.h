#pragma once
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"
#include "../GameActor.h"

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}

	namespace nsPlayer {

		//�v���C���[�N���X
		class CPlayer : public IGameActor
		{
		public:
			static const char* const m_kObjName_Player;		//�v���C���[�N���X�̖��O
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void UpdateActor(float deltaTime)override final;

			void ApplyDamage(float power, bool canGuard = true)override final;

			void HealHP(float healValue)override final {

				//HP���񕜁B
				m_status.HealHP(healValue);
			}
			void HealMP(float healValue)override final {

				//MP���񕜁B
				m_status.HealMP(healValue);
			}
			void HealSP(float healValue)override final {

				//SP���񕜁B
				m_status.HealSP(healValue);
			}
		public:
			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_action.GetPosition();
			}

			const CQuaternion& GetRotation()const {

				//��]�����擾�B
				return m_action.GetRotation();
			}

			CPlayerStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon()override final;

			nsArmor::CArmor* GetArmor()override final;

			void SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill);
		private:
			void CreatePlayerModel();

			void CreateWeapon();

			void CreateArmor();
		private:
			CModelRenderer* m_modelRenderer = nullptr;				//�v���C���[���f��
			CPlayerInput m_input;									//����
			CPlayerAction m_action;									//�A�N�V����
			CPlayerStatus m_status;									//�X�e�[�^�X
			nsWeapon::CWeapon* m_weapon = nullptr;					//����
			nsArmor::CArmor* m_armor = nullptr;						//�h��

#ifdef _DEBUG
			CFontRenderer* m_fontRenderer = nullptr;
			wchar_t m_dispText[32] = {};
#endif		
		};
	}
}

