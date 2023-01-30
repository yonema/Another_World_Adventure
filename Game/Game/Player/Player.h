#pragma once
#include "../GameActor.h"
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"
#include "PlayerAnimation/PlayerAnimation.h"
#include "PlayerCollider.h"
#include "PlayerWeaponManager.h"

namespace nsAWA {

	//�O���錾
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
			bool StartSub()override final;

			void OnDestroySub()override final;

			void UpdateActor(float deltaTime)override final;

			void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true)override final;

			bool IsDeath()const override final {

				//HP��0�ȉ����ǂ��������^�[���B
				return m_status.GetHP() <= FLT_EPSILON;
			}

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
			CPlayerAction& GetPlayerAction() {

				//�v���C���[�A�N�V�����N���X���擾�B
				return m_action;
			}

			CPlayerStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon()override final;

			nsArmor::CArmor* GetArmor()override final;

			CGameActorCollider* GetGameActorCollider() {

				//�A�N�^�[�̓����蔻����擾�B
				return &m_collider;
			}

			void SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill);

			void SetWeapon(nsWeapon::CWeapon* weapon);

		private:
			void CreatePlayerModel();

		private:
			CPlayerInput m_input;									//����
			CPlayerAction m_action;									//�A�N�V����
			nsPlayerAnimation::CPlayerAnimation m_animation;		//�A�j���[�V����
			CPlayerStatus m_status;									//�X�e�[�^�X
			nsArmor::CArmor* m_armor = nullptr;						//�h��
			CPlayerCollider m_collider;								//�v���C���[�̓����蔻��
			CPlayerWeaponManager m_weaponManager;					//����Ǘ��N���X

#ifdef _DEBUG
			CFontRenderer* m_fontRenderer = nullptr;
			wchar_t m_dispText[32] = {};
#endif		
		};
	}
}

