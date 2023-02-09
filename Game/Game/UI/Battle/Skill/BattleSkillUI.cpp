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
            // �X�L���A�C�R���U����UI�N���X���쐬
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
            // ���t���[���̏�����������

        }

        void CBattleSkillUI::Animation()
        {

        }
    }
}