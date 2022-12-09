#pragma once
#include "../GameActorCollider.h"

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsPlayer {

		//プレイヤーの当たり判定クラス
		class CPlayerCollider : public CGameActorCollider
		{
		public:
			void CreateCollider();

			void Update();

			void Release();

		public:
			CPlayer* GetPlayer() {

				//プレイヤーのポインタをリターン。
				return m_player;
			}

		private:
			CPhysicsTriggerObject m_triggerBox;		//当たり判定
			const CVector3* m_position = nullptr;	//座標

			CPlayer* m_player = nullptr;	//プレイヤーのポインタ
		};
	}
}