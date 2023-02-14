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

	//�O���錾
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

		//�v���C���[�N���X
		class CPlayer : public IGameActor
		{
		public:
			static const char* const m_kObjName_Player;		//�v���C���[�N���X�̖��O
		public:
			bool StartSub()override final;

			void OnDestroySub()override final;

			void UpdateActor(float deltaTime)override final;

			void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true)override final;

			bool IsDeath()const override final {

				//HP��0�ȉ����ǂ��������^�[���B
				return m_status.GetHP() <= FLT_EPSILON;
			}

			void HealHP(float healValue)override final {

				//HP���񕜁B
				m_status.HealHP(healValue);
			}
			void HealMP(float healValue)override final {

				//MP���񕜁B
				m_status.HealMP(healValue);
			}
			void HealSP(float healValue)override final {

				//SP���񕜁B
				m_status.HealSP(healValue);
			}
			void AddExp(int exp) {

				//�o���l���l���B
				m_status.AddExp(exp);
			}

		public:
			CPlayerAction& GetPlayerAction() {

				//�v���C���[�A�N�V�����N���X���擾�B
				return m_action;
			}

			void InputEnable() {

				//���͂ł����Ԃɂ���B
				m_input.InputEnable();
			}

			void InputDisable() {

				//���͂ł��Ȃ���Ԃɂ���B
				m_input.InputDisable();
			}

			CPlayerStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon();

			CPlayerWeaponManager* GetWeaponManager() {

				//����Ǘ��N���X���擾�B
				return &m_weaponManager;
			}

			nsArmor::CArmor* GetArmor();

			CGameActorCollider* GetGameActorCollider() {

				//�A�N�^�[�̓����蔻����擾�B
				return &m_collider;
			}

			void SetActiveSkill(int setNum, nsSkill::CActiveSkill* activeSkill);

			nsSkill::CActiveSkill* GetActiveSkill(int skillNum)const;

			void SetWeapon(nsWeapon::CWeapon* weapon);

			void SetArmor(nsArmor::CArmor* armor);


			void SetPlayerName(const std::string& playerName) {

				//�v���C���[�l�[����ݒ�B
				m_status.SetPlayerName(playerName);
			}

			void SetIsInTown(bool flag) {

				//�X�����ǂ�����ݒ�B
				m_isInTown = flag;
			}

			bool IsInTown()const {

				//�X���H
				return m_isInTown;
			}

		public:	//�˗��֘A
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
			bool m_isInTown = false;								//�X���H
			CPlayerInput m_input;									//����
			CPlayerAction m_action;									//�A�N�V����
			nsPlayerAnimation::CPlayerAnimation m_animation;		//�A�j���[�V����
			CPlayerStatus m_status;									//�X�e�[�^�X
			nsArmor::CArmor* m_armor = nullptr;						//�h��
			CPlayerCollider m_collider;								//�v���C���[�̓����蔻��
			CPlayerWeaponManager m_weaponManager;					//����Ǘ��N���X
			CPlayerQuestManager m_questManager;						//�N�G�X�g�Ǘ��N���X
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

