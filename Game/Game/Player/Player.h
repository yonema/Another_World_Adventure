#pragma once
#include "../GameActor.h"
#include "PlayerStatus.h"
#include "PlayerAction.h"
#include "PlayerInput.h"
#include "PlayerAnimation/PlayerAnimation.h"
#include "PlayerCollider.h"
#include "PlayerWeaponManager.h"
#include "PlayerQuestManager.h"

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
		class CMenuManager;
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
			void AddExp(int exp) {

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

			CPlayerWeaponManager* GetWeaponManager() {

				//武器管理クラスを取得。
				return &m_weaponManager;
			}

			nsArmor::CArmor* GetArmor();

			CGameActorCollider* GetGameActorCollider() {

				//アクターの当たり判定を取得。
				return &m_collider;
			}

			void SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill);

			nsSkill::CActiveSkill* GetActiveSkill(int skillNum)const;

			void SetWeapon(nsWeapon::CWeapon* weapon);

			void SetArmor(nsArmor::CArmor* armor);


			void SetPlayerName(const std::string& playerName) {

				//プレイヤーネームを設定。
				m_status.SetPlayerName(playerName);
			}

			void SetIsInTown(bool flag) {

				//街中かどうかを設定。
				m_isInTown = flag;
			}

			bool IsInTown()const {

				//街中？
				return m_isInTown;
			}

		public:	//依頼関連
			void SetSlayQuest(const std::string& questName, const std::string& targetEnemyName, int slayToCompleteNum)
			{
				m_questManager.SetSlayQuest(questName, targetEnemyName, slayToCompleteNum);
			}

			bool IsQuestReceived(const std::string& questName)
			{
				return m_questManager.IsQuestReceived(questName);
			}

			bool IsQuestCompleted(const std::string& questName)
			{
				return m_questManager.IsQuestCompleted(questName);
			}

			void ProgressSlayQuest(const std::string& slayMonsterName)
			{
				m_questManager.Progress(slayMonsterName);
			}

			void EraseQuest(const std::string& eraseQuestName)
			{

				//m_questManager.Reset();

				m_questManager.EraseQuest(eraseQuestName);


			}
		private:
			void CreatePlayerModel();

		public: // UI
			void ChangeFromSkillToItemUI();

			void ChangeFromItemToSkillUI();

			void MoveNextItemUI();

			void MoveBackItemUI();

		private:
			bool m_isInTown = false;								//街中？
			CPlayerInput m_input;									//入力
			CPlayerAction m_action;									//アクション
			nsPlayerAnimation::CPlayerAnimation m_animation;		//アニメーション
			CPlayerStatus m_status;									//ステータス
			nsArmor::CArmor* m_armor = nullptr;						//防具
			CPlayerCollider m_collider;								//プレイヤーの当たり判定
			CPlayerWeaponManager m_weaponManager;					//武器管理クラス
			CPlayerQuestManager m_questManager;						//クエスト管理クラス
#ifdef _DEBUG
			CFontRenderer* m_fontRenderer = nullptr;
			wchar_t m_dispText[32] = {};
#endif		
			nsUI::CPlayerBattleStatusUI* m_playerBattleStatusUI = nullptr;
			nsUI::CSkillIconUI* m_skillIconUI = nullptr;
			nsUI::CItemUI* m_itemUI = nullptr;
			nsUI::CMenuManager* m_menuManager;

		};
	}
}

