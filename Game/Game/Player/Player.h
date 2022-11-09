#pragma once
#include "PlayerInput.h"

namespace nsAWA {

	namespace nsPlayer {

		//プレイヤークラス
		class CPlayer : public IGameObject
		{
		public:
			static const char* const m_kObjName_Player;		//プレイヤークラスの名前
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		public:
			const CVector3& GetPosition()const {

				//座標を取得。
				return m_action.GetPosition();
			}
		private:
			void CreatePlayerModel();
		private:
			CModelRenderer* m_modelRenderer = nullptr;	//プレイヤーモデル
			CPlayerInput m_input;						//入力
			CPlayerAction m_action;						//アクション
		};
	}
}

