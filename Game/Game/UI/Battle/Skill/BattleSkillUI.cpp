#include "YonemaEnginePreCompile.h"
#include "BattleSkillUI.h"

#include "../../SpriteUI.h"
#include "SkillIconUI.h"
namespace nsAWA
{
    namespace nsUI
    {
        bool CBattleSkillUI::Start()
        {
            return true;
        }

        void CBattleSkillUI::LoadLevel(const char* tdlFilePath)
        {
            // スキルアイコン６つ分のUIクラスを作成
            for (auto& forUI : m_skillIconUI) {
                forUI = NewGO<CSkillIconUI>();
                //forUI->LoadLevel(tdlFilePath);
            }
        }

        void CBattleSkillUI::OnDestroy()
        {
            for (auto& forUI : m_skillIconUI) {
                DeleteGO(forUI);
            }
        }

        void CBattleSkillUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

        }

        void CBattleSkillUI::Animation()
        {

        }
    }
}