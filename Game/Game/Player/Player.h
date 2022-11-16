#pragma once
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"

namespace nsAWA {

	namespace nsWeapon {

		class CWeapon;
	}

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

			void ApplyDamage(int power);

		public:
			const CVector3& GetPosition()const {

				//座標を取得。
				return m_action.GetPosition();
			}

			const CQuaternion& GetRotation()const {

				//回転情報を取得。
				return m_action.GetRotation();
			}

			CPlayerStatus* GetStatus() {

				//ステータスを受け取る。
				return &m_status;
			}
		private:
			void CreatePlayerModel();

			void CreateWeapon();
		private:
			CModelRenderer* m_modelRenderer = nullptr;	//プレイヤーモデル
			CPlayerInput m_input;						//入力
			CPlayerAction m_action;						//アクション
			CPlayerStatus m_status;						//ステータス
			nsWeapon::CWeapon* m_weapon = nullptr;		//武器
		};
	}
}

