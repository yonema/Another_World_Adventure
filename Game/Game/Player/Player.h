#pragma once
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"
#include "../GameActor.h"

namespace nsAWA {

	//エイリアス宣言
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}

	namespace nsPlayer {

		//プレイヤークラス
		class CPlayer : public IGameActor
		{
		public:
			static const char* const m_kObjName_Player;		//プレイヤークラスの名前
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void UpdateActor(float deltaTime)override final;

			void ApplyDamage(float power, bool canGuard = true)override final;

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

			void CreateArmor();
		private:
			CModelRenderer* m_modelRenderer = nullptr;	//プレイヤーモデル
			CPlayerInput m_input;						//入力
			CPlayerAction m_action;						//アクション
			CPlayerStatus m_status;						//ステータス
			nsWeapon::CWeapon* m_weapon = nullptr;		//武器
			nsArmor::CArmor* m_armor = nullptr;			//防具
		};
	}
}

