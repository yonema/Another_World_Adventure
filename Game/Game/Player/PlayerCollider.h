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

		public:
			CPlayer* GetPlayer() {

				//プレイヤーのポインタをリターン。
				return m_player;
			}

			bool IsReleased()const {

				//破棄されたかどうかをリターン。
				return m_released;
			}

		private:
			bool m_released = false;				//破棄された？
			const CVector3* m_position = nullptr;	//座標

			CPlayer* m_player = nullptr;	//プレイヤーのポインタ
		};
	}
}