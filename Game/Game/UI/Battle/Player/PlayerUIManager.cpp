#include "YonemaEnginePreCompile.h"
#include "PlayerUIManager.h"

#include "PlayerBattleStatusUI.h"
#include "../Skill/SkillIconUI.h"
#include "../Item/ItemUI.h"
#include "../../Menu/MenuManager.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CPlayerUIManager::Start()
        {
            m_menuManager = NewGO<nsUI::CMenuManager>();

            LoadLevel();

            return true;
        }

        void CPlayerUIManager::LoadLevel()
        {
            m_playerBattleStatusUI = NewGO<nsUI::CPlayerBattleStatusUI>();
            m_playerBattleStatusUI->LoadLevel();

            m_skillIconUI = NewGO<nsUI::CSkillIconUI>();
            m_skillIconUI->LoadLevel();

            m_itemUI = NewGO<nsUI::CItemUI>();
            m_itemUI->LoadLevel();
        }

        void CPlayerUIManager::OnDestroy()
        {
            DeleteGO(m_playerBattleStatusUI);
            DeleteGO(m_skillIconUI);
            DeleteGO(m_itemUI);
            DeleteGO(m_menuManager);
        }

        void CPlayerUIManager::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            //if (Input()->IsTrigger(EnActionMapping::enMenu)) {
            //    if (false == m_flagTest) {
            //        ActivatePlayerBattleStatusDrawingFlag();

            //        m_flagTest = true;
            //    }
            //    else {
            //        DeactivatePlayerBattleStatusDrawingFlag();
            //        m_flagTest = false;
            //    }
            //}

        }

        void CPlayerUIManager::SetUIPlayerStatus(
            const float hp, const float maxHP,
            const float mp, const float maxMP,
            const float sp, const float maxSP
        )
        {
            // UIにプレイヤーのステータスを渡す
            m_playerBattleStatusUI->SetUIPlayerStatus(hp, maxHP, mp, maxMP, sp, maxSP);
        }

        void CPlayerUIManager::ActivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_playerBattleStatusUI->ActivatePlayerBattleStatusDrawingFlag();
            m_skillIconUI->ActivatePlayerBattleStatusDrawingFlag();
            m_itemUI->ActivatePlayerBattleStatusDrawingFlag();

            m_playerBattleStatusUI->Activate();
            m_skillIconUI->Activate();
            m_itemUI->Activate();
        }

        void CPlayerUIManager::DeactivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_playerBattleStatusUI->DeactivatePlayerBattleStatusDrawingFlag();
            m_skillIconUI->DeactivatePlayerBattleStatusDrawingFlag();
            m_itemUI->DeactivatePlayerBattleStatusDrawingFlag();

            m_playerBattleStatusUI->Deactivate();
            m_skillIconUI->Deactivate();
            m_itemUI->Deactivate();
        }

        void CPlayerUIManager::ChangeFromSkillToItemUI()
        {
            m_skillIconUI->DeactiveDrawing();
            m_itemUI->ActiveDrawing();
        }

        void CPlayerUIManager::ChangeFromItemToSkillUI()
        {
            m_itemUI->DeactiveDrawing();
            m_skillIconUI->ActiveDrawing();
        }

        void CPlayerUIManager::MoveNextItemUI()
        {
            m_itemUI->MoveNextItemUI();
        }

        void CPlayerUIManager::MoveBackItemUI()
        {
            m_itemUI->MoveBackItemUI();
        }

    }

}