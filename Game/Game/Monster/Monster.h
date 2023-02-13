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
	namespace nsUI {

		class CEnemyBattleStatusUI;
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
			enBark,				//�i����
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

			bool IsDeath()const override final {

				//HP��0�ȉ����ǂ��������^�[���B
				return m_status.GetHP() <= FLT_EPSILON;
			}

			void HealHP(float healValue)override final {

				//HP���񕜁B
				m_status.HealHP(healValue);
			}
			void HealMP(float healValue)override final {};
			void HealSP(float healValue)override final {};

			void SetForwardDirection(const CVector3& forwardDirection) {

				//�O������ݒ�B
				m_forwardDirection = forwardDirection;
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

			CGameActorCollider* GetGameActorCollider() {

				CGameActorCollider* col = nullptr;
				return col;
			}

			const std::string& GetMonsterName()const {

				//���O���擾�B
				return m_name;
			}

			int GetDropExp()const {

				//�l���o���l�ʂ��擾�B
				return m_dropExp;
			}

			const std::list<std::string>& GetDropItemList()const {

				//�h���b�v�A�C�e�����X�g���擾�B
				return m_dropItemList;
			}

			bool CheckDrop(const std::string& dropItemName);

		private:
			void CreateMonsterModel(const SMonsterInitData& monsterInfo);

		private:
			std::string m_name = "NoName";				//���O
			int m_dropExp = 0;							//�l���o���l��
			std::list<std::string> m_dropItemList;		//�h���b�v�A�C�e�����X�g

			CMonsterCollider m_collider;				//�R���C�_�[
			CMonsterStatus m_status;					//�X�e�[�^�X
			CMonsterAnimation m_animation;				//�A�j���[�V����
			nsMonsterAI::CMonsterAIController m_AIContoller;	//AI�R���g���[���[
			EnMonsterState m_state = static_cast<EnMonsterState>(-1);	//�X�e�[�g
			bool m_isChangeState = false;	//�X�e�[�g�����̃t���[���ŕύX���ꂽ�H

			nsUI::CEnemyBattleStatusUI* m_enemyBattleStatusUI = nullptr;
		};
	}
}

