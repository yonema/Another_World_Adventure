#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"
#include "MonsterAnimation.h"
#include "MonsterCollider.h"
#include "AI/MonsterAIController.h"

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

			

			void SetPosition(const CVector3& position) {

				//���W��ݒ�B
				m_position = position;
			}

			const CVector3& GetPosition()const override final {

				//���W���擾�B
				return m_position;
			}

			void SetRotation(const CQuaternion& rotation) {

				//��]��ݒ�B
				m_rotation = rotation;
			}

			const CQuaternion& GetRotation()const {

				//��]���擾�B
				return m_rotation;
			}

			void SetForwardDirection(const CVector3& forwardDirection) {

				//�O������ݒ�B
				m_forwardDirection = forwardDirection;
			}

			const CVector3& GetForwardDirection()const override final {

				//�O�������擾�B
				return m_forwardDirection;
			}
		public:
			void SetState(const EnMonsterState& state) {

				//�X�e�[�g���ς������B
				if (m_state != state) {

					//�V�����X�e�[�g��ݒ肷��B
					m_state = state;

					//�X�e�[�g�ɕύX���������B
					m_isChangeState = true;
				}
			}

			const EnMonsterState& GetState()const {

				//�X�e�[�g���擾�B
				return m_state;
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
			const char* m_name = nullptr;				//���O
			CModelRenderer* m_modelRenderer = nullptr;	//���f��

			CVector3 m_position = CVector3::Zero();		//���W
			CQuaternion m_rotation = CQuaternion::Identity();	//��]
			CVector3 m_forwardDirection = CVector3::Zero();		//�O����

			CMonsterCollider m_collider;				//�R���C�_�[
			CMonsterStatus m_status;					//�X�e�[�^�X
			CMonsterAnimation m_animation;				//�A�j���[�V����
			nsMonsterAI::CMonsterAIController m_AIContoller;	//AI�R���g���[���[
			EnMonsterState m_state = static_cast<EnMonsterState>(-1);	//�X�e�[�g
			bool m_isChangeState = false;	//�X�e�[�g�����̃t���[���ŕύX���ꂽ�H
			nsWeapon::CWeapon* m_weapon = nullptr;		//����
			nsArmor::CArmor* m_armor = nullptr;			//�h��
		};
	}
}

