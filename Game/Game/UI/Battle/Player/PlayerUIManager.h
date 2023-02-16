#pragma once

namespace nsAWA
{
	namespace nsUI
	{
		class CPlayerBattleStatusUI;
		class CSkillIconUI;
		class CItemUI;
		class CMenuManager;

		//プレイヤー管理クラス
		class CPlayerUIManager : public IGameObject
		{
		public:
			bool Start() override final;

			void OnDestroy() override final;

			void Update(float deltaTime) override final;

		public:
			CPlayerUIManager() = default;
			~CPlayerUIManager() = default;



		public:
			void LoadLevel();



		public:
			void SetUIPlayerStatus(
				const float hp, const float maxHP,
				const float mp, const float maxMP,
				const float sp, const float maxSP
			);

			void ActivatePlayerBattleStatusDrawingFlag();

			void DeactivatePlayerBattleStatusDrawingFlag();

			void ChangeFromSkillToItemUI();

			void ChangeFromItemToSkillUI();

			void MoveNextItemUI();

			void MoveBackItemUI();



		private: // data member
			CPlayerBattleStatusUI* m_playerBattleStatusUI = nullptr;
			CSkillIconUI* m_skillIconUI = nullptr;
			CItemUI* m_itemUI = nullptr;
			CMenuManager* m_menuManager = nullptr;

			bool m_flagTest = true;
		};

	}


}