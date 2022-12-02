#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsMonster {

		enum class EnMonsterState;
		enum class EnMonsterList;
	}

	namespace nsMonster {

		//モンスターアニメーションクラス
		class CMonsterAnimation : nsUtils::SNoncopyable
		{
		public:
			void Init(CModelRenderer* monsterModel, EnMonsterList monster);

			void Update(bool changeState, EnMonsterState state);

		private:
			void PlayAnimation(EnMonsterState state);

		private:
			EnMonsterList m_monster = static_cast<EnMonsterList>(-1);	//何のモンスターか
			CModelRenderer* m_monsterModel = nullptr;	//モンスターのモデル
		};
	}
}

