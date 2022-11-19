#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"

namespace nsAWA {

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
			bool Start()override final;

			void OnDestroy()override final;

			void UpdateActor(float deltaTime)override final;

			void Create(const SMonsterInfo& monsterInfo);

			void ApplyDamage(float power, bool canGuard = true)override final;
		public:

			CStatus* GetStatus()override final;
		private:
			void CreateMonsterModel(const SMonsterInfo& monsterInfo);
		private:
			const char* m_name = nullptr;
			CModelRenderer* m_modelRenderer = nullptr;	//モデル
			CMonsterStatus m_status;					//ステータス
		};
	}
}

