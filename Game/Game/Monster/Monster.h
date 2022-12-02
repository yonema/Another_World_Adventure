#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"

namespace nsAWA {

	//前方宣言
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}

	namespace nsMonster {

		//モンスター情報
		struct SMonsterInfo {

			const char* name;						//モンスター名
			const char* modelFilePath = nullptr;	//モデルのファイルパス
		};

		//モンスタークラス
		class CMonster : public IGameActor
		{
		public:
			static const char* const m_kObjName_Monster;		//モンスタークラスの名前
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
			CModelRenderer* m_modelRenderer = nullptr;	//モデル
			CMonsterStatus m_status;					//ステータス
			nsWeapon::CWeapon* m_weapon = nullptr;		//武器
			nsArmor::CArmor* m_armor = nullptr;			//防具
		};
	}
}

