#pragma once
#include "../GameActor.h"
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"
#include "PlayerAnimation/PlayerAnimation.h"
#include "PlayerCollider.h"
#include "PlayerWeaponManager.h"

namespace nsAWA {

	//前方宣言
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
			bool StartSub()override final;

			void OnDestroySub()override final;

			void UpdateActor(float deltaTime)override final;

			void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true)override final;

			bool IsDeath()const override final {

				//HPが0以下かどうかをリターン。
				return m_status.GetHP() <= FLT_EPSILON;
			}

			void HealHP(float healValue)override final {

				//HPを回復。
				m_status.HealHP(healValue);
			}
			void HealMP(float healValue)override final {

				//MPを回復。
				m_status.HealMP(healValue);
			}
			void HealSP(float healValue)override final {

				//SPを回復。
				m_status.HealSP(healValue);
			}

		public:
			CPlayerAction& GetPlayerAction() {

				//プレイヤーアクションクラスを取得。
				return m_action;
			}

			CPlayerStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon()override final;

			nsArmor::CArmor* GetArmor()override final;

			CGameActorCollider* GetGameActorCollider() {

				//アクターの当たり判定を取得。
				return &m_collider;
			}

			void SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill);

			void SetWeapon(nsWeapon::CWeapon* weapon);

		private:
			void CreatePlayerModel();

		private:
			CPlayerInput m_input;									//入力
			CPlayerAction m_action;									//アクション
			nsPlayerAnimation::CPlayerAnimation m_animation;		//アニメーション
			CPlayerStatus m_status;									//ステータス
			nsArmor::CArmor* m_armor = nullptr;						//防具
			CPlayerCollider m_collider;								//プレイヤーの当たり判定
			CPlayerWeaponManager m_weaponManager;					//武器管理クラス

#ifdef _DEBUG
			CFontRenderer* m_fontRenderer = nullptr;
			wchar_t m_dispText[32] = {};
#endif		
		};
	}
}

