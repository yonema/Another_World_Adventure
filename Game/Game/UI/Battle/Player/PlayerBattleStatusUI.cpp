#include "YonemaEnginePreCompile.h"
#include "PlayerBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "PlayerHPUI.h"
#include "PlayerMPUI.h"
#include "PlayerSPUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerBattleStatusUI::m_kLevel2DFilePath =
            "Assets/Level2D/PlayerStatus.tdl";

        const char* CPlayerBattleStatusUI::m_kSpritePlayerStatusBaseFilePath =
            "Assets/Images/FitnessBar/Player/PlayerStatusBase.png";

        bool CPlayerBattleStatusUI::Start()
        {
            return true;
        }

        void CPlayerBattleStatusUI::LoadLevel()
        {
            // �v���C���[�̃o�g���X�e�[�^�X�̓y��
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �v���C���[�X�e�[�^�X�̓y�䕔��
                    if ("PlayerStatusBase" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spritePlayerStatusBase = NewGO<CSpriteUI>();
                        m_spritePlayerStatusBase->LoadSprite(
                            m_kSpritePlayerStatusBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spritePlayerStatusBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );
                        
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });

            // �v���C���[��HP�Q�[�W
            m_playerHPUI = NewGO<CPlayerHPUI>();
            m_playerHPUI->LoadLevel();

            // �v���C���[��MP�Q�[�W
            m_playerMPUI = NewGO<CPlayerMPUI>();
            m_playerMPUI->LoadLevel();

            // �v���C���[��SP�Q�[�W
            m_playerSPUI = NewGO<CPlayerSPUI>();
            m_playerSPUI->LoadLevel();
        }

        void CPlayerBattleStatusUI::OnDestroy()
        {
            DeleteGO(m_spritePlayerStatusBase);

            DeleteGO(m_playerHPUI);
            DeleteGO(m_playerMPUI);
            DeleteGO(m_playerSPUI);
        }

        void CPlayerBattleStatusUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������



        }

        void CPlayerBattleStatusUI::SetUIPlayerStatus(
            const float hp, const float maxHP,
            const float mp, const float maxMP,
            const float sp, const float maxSP
        )
        {
            m_playerHPUI->SetUIPlayerHPStatus(hp, maxHP);
            m_playerMPUI->SetUIPlayerMPStatus(mp, maxMP);
            m_playerSPUI->SetUIPlayerSPStatus(sp, maxSP);
        }
    }
}