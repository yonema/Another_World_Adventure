#pragma once
#include "../GameActor.h"

namespace nsAWA {

	namespace nsMonster {

		//モンスター情報
		struct SMonsterInfo {

			const char* name;						//モンスター名
			const char* modelFilePath = nullptr;	//モデルのファイルパス
		};

		//モンスタークラス
		class CMonster : public CGameActor
		{
		public:
			static const char* const m_kObjName_Monster;		//モンスタークラスの名前
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void Create(const SMonsterInfo& monsterInfo);

		private:
			void CreateMonsterModel(const SMonsterInfo& monsterInfo);
		private:
			const char* m_name = nullptr;
			CModelRenderer* m_modelRenderer = nullptr;	//モデル
		};
	}
}

