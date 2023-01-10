#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"
#include "MonsterAnimation.h"
#include "MonsterCollider.h"

namespace nsAWA {

	//�O���錾
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}
	namespace nsMonster {

		enum class EnMonsterList;
		enum class EnMonsterState;
		struct SMonsterInitData;
	}

	namespace nsMonster {

		//�����X�^�[�̃X�e�[�g
		enum class EnMonsterState {

			enIdle,				//�ҋ@
			enWalk,				//����
			enRun,				//����
			enWeakAttack,		//��U��
			enStrongAttack,		//���U��
			enDamage,			//��e
			enDeath,			//���S

			enNum,		//�X�e�[�g�̐�
			enNone = -1	//�ݒ�Ȃ�
		};

		//�����X�^�[�N���X
		class CMonster : public IGameActor
		{
		public:
			static const char* const m_kObjName_Monster;		//�����X�^�[�N���X�̖��O

		public:
			bool StartSub()override final;

			void OnDestroySub()override final;

			void UpdateActor(float deltaTime)override final;

			void Create(const SMonsterInitData& monsterInfo);

			void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true)override final;

			void HealHP(float healValue)override final {};
			void HealMP(float healValue)override final {};
			void HealSP(float healValue)override final {};

			const CVector3& GetPosition()const override final {

				//���W���擾�B�i�������j
				return CVector3::Zero();
			}

			const CVector3& GetForwardDirection()const override final {

				//�O�������擾�B�i�������j
				return CVector3::Zero();
			}
		public:
			void SetState(EnMonsterState state) {

				//�X�e�[�g���ς������B
				if (m_state != state) {

					//�V�����X�e�[�g��ݒ肷��B
					m_state = state;

					//�X�e�[�g�ɕύX���������B
					m_isChangeState = true;
				}
			}

			CStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon()override final;

			nsArmor::CArmor* GetArmor()override final;

			CGameActorCollider* GetGameActorCollider() {

				CGameActorCollider* col = nullptr;
				return col;
			}

		private:
			void CreateMonsterModel(const SMonsterInitData& monsterInfo);

		private:
			const char* m_name = nullptr;
			CModelRenderer* m_modelRenderer = nullptr;	//���f��
			CMonsterCollider m_collider;				//�R���C�_�[
			CMonsterStatus m_status;					//�X�e�[�^�X
			CMonsterAnimation m_animation;				//�A�j���[�V����
			EnMonsterState m_state = static_cast<EnMonsterState>(-1);	//�X�e�[�g
			bool m_isChangeState = false;	//�X�e�[�g�����̃t���[���ŕύX���ꂽ�H
			nsWeapon::CWeapon* m_weapon = nullptr;		//����
			nsArmor::CArmor* m_armor = nullptr;			//�h��
		};
	}
}

