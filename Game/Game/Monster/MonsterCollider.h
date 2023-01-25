#pragma once
#include "../GameActorCollider.h"

namespace nsAWA {

	//前方宣言
	namespace nsMonster {

		class CMonster;
	}

	namespace nsMonster {

		//モンスター当たり判定クラス
		class CMonsterCollider : public CGameActorCollider
		{
		public:
			void CreateCollider();

			void Update();

			void Release();

		public:
			CMonster* GetGameActor() {

				//モンスターのポインタをリターン。
				return m_monster;
			}

			bool IsReleased()const {

				//破棄されたかどうかをリターン。
				return m_released;
			}

		private:
			bool m_released = false;				//破棄された？
			CPhysicsTriggerObject m_triggerBox;		//当たり判定
			const CVector3* m_position = nullptr;	//座標
			CMonster* m_monster = nullptr;			//モンスターのポインタ
		};
	}
}