#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"

namespace nsAWA {

	//�O���錾
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}

	namespace nsMonster {

		//�����X�^�[���
		struct SMonsterInfo {

			const char* name;						//�����X�^�[��
			const char* modelFilePath = nullptr;	//���f���̃t�@�C���p�X
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

			void Create(const SMonsterInfo& monsterInfo);

			void ApplyDamage(float power, bool canGuard = true)override final;

			void HealHP(float healValue)override final {};
			void HealMP(float healValue)override final {};
			void HealSP(float healValue)override final {};
		public:

			CStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon()override final;

			nsArmor::CArmor* GetArmor()override final;
		private:
			void CreateMonsterModel(const SMonsterInfo& monsterInfo);
		private:
			const char* m_name = nullptr;
			CModelRenderer* m_modelRenderer = nullptr;	//���f��
			CMonsterStatus m_status;					//�X�e�[�^�X
			nsWeapon::CWeapon* m_weapon = nullptr;		//����
			nsArmor::CArmor* m_armor = nullptr;			//�h��
		};
	}
}

