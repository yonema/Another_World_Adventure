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
            // プレイヤーのバトルステータスの土台
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // プレイヤーステータスの土台部分
                    if ("PlayerStatusBase" == imgData.Name)
                    {
                        // UIクラスを作成
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
                        
                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });

            // プレイヤーのHPゲージ
            m_playerHPUI = NewGO<CPlayerHPUI>();
            m_playerHPUI->LoadLevel();

            // プレイヤーのMPゲージ
            m_playerMPUI = NewGO<CPlayerMPUI>();
            m_playerMPUI->LoadLevel();

            // プレイヤーのSPゲージ
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
            // 毎フレームの処理をここに



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