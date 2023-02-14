#include "YonemaEnginePreCompile.h"
#include "MenuManager.h"

#include "../SpriteUI.h"
#include "Skill/MenuSkillWindowUI.h"
#include "Skill/OperationMenuSkillUI.h"
#include "../../Player/PlayerManager.h"
#include "MenuBaseUI.h"


namespace nsAWA
{
    namespace nsUI
    {
        bool CMenuManager::Start()
        {

            return true;
        }

        void CMenuManager::OnDestroy()
        {
            DeleteGO(m_menuBaseUI);
        }

        void CMenuManager::Update(float deltaTime)
        {
            // ƒƒjƒ…[‚ÌŠJ•Â
            if (Input()->IsTrigger(EnActionMapping::enMenu)) {
                if (false == m_flagOpenMenu) {
                    OpenMenu();
                }
                else {
                    CloseMenu();
                }
            }
        }

        const bool CMenuManager::OpenMenu()
        {
            if (true == m_flagOpenMenu) {
                return false;
            }

            m_menuBaseUI = NewGO<CMenuBaseUI>();
            m_menuBaseUI->LoadLevel();

            nsPlayer::CPlayerManager::GetInstance()->InputDisable();

            m_flagOpenMenu = true;

            return true;
        }

        const bool CMenuManager::CloseMenu()
        {
            if (false == m_flagOpenMenu) {
                return false;
            }

            DeleteGO(m_menuBaseUI);

            nsPlayer::CPlayerManager::GetInstance()->InputEnable();

            m_flagOpenMenu = false;

            return true;
        }


    }
}