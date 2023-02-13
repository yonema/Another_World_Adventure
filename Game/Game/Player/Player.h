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
	namespace nsUI {
		
		class CPlayerBattleStatusUI;
		class CSkillIconUI;
		class CItemUI;
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
			void AddExp(float exp) {

				//経験値を獲得。
				m_status.AddExp(exp);
			}

		public:
			CPlayerAction& GetPlayerAction() {

				//プレイヤーアクションクラスを取得。
				return m_action;
			}

			void InputEnable() {

				//入力できる状態にする。
				m_input.InputEnable();
			}

			void InputDisable() {

				//入力できない状態にする。
				m_input.InputDisable();
			}

			CPlayerStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon();

			nsArmor::CArmor* GetArmor();

			CGameActorCollider* GetGameActorCollider() {

				//アクターの当たり判定を取得。
				return &m_collider;
			}

			void SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill);

			nsSkill::CActiveSkill* GetActiveSkill(int skillNum)const;

			void SetWeapon(nsWeapon::CWeapon* weapon);

			void SetArmor(nsArmor::CArmor* armor);

		private:
			void CreatePlayerModel();

		public: // UI
			void ChangeFromSkillToItemUI();

			void ChangeFromItemToSkillUI();

			void MoveNextItemUI();

			void MoveBackItemUI();

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
			nsUI::CPlayerBattleStatusUI* m_playerBattleStatusUI = nullptr;
			nsUI::CSkillIconUI* m_skillIconUI = nullptr;
			nsUI::CItemUI* m_itemUI = nullptr;

		};
	}
}

