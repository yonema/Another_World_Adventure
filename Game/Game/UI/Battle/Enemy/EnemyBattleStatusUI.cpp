#include "YonemaEnginePreCompile.h"
#include "EnemyBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "EnemyHPUI.h"
#include "EnemyBreakUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBattleStatusUI::m_kLevel2DFilePath =
            "Assets/Level2D/EnemyStatusBase.tdl";

        const char* CEnemyBattleStatusUI::m_kSpriteEnemyStatusBaseFilePath = 
            "Assets/Images/FitnessBar/Enemy/EnemyStatusBase.png";

        bool CEnemyBattleStatusUI::Start()
        {
            return true;
        }

        void CEnemyBattleStatusUI::LoadLevel()
        {
            // プレイヤーのバトルステータスの土台
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // 敵ステータスの土台部分
                    if ("EnemyStatusBase" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteEnemyStatusBase = NewGO<CSpriteUI>();
                        m_spriteEnemyStatusBase->LoadSprite(
                            m_kSpriteEnemyStatusBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteEnemyStatusBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // 土台部分以外のUIの位置の基準になる位置を取得
                        m_basePosition = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });

            // 敵のHPゲージ
            m_enemyHPUI = NewGO<CEnemyHPUI>();
            m_enemyHPUI->LoadLevel(m_basePosition);

            // 敵のブレイクゲージ
            //m_enemyBreakUI = NewGO<CEnemyBreakUI>();
            //m_enemyBreakUI->LoadLevel(m_basePosition);
        }

        void CEnemyBattleStatusUI::OnDestroy()
        {
            DeleteGO(m_spriteEnemyStatusBase);

            DeleteGO(m_enemyHPUI);
            DeleteGO(m_enemyBreakUI);
        }

        void CEnemyBattleStatusUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに



        }

        void CEnemyBattleStatusUI::SetUIEnemyStatus(const float hp, const float maxHP, const float breakBar)
        {
            m_enemyHPUI->SetUIEnemyHPStatus(hp, maxHP);
            //m_enemyBreakUI->SetUIEnemyBreakStatus(breakBar);
        }

        void CEnemyBattleStatusUI::SetUIEnemyPosition(const CVector3& position)
        {
            // これだと、全部一か所にまとまるので、
            // 補正値を追加で入れること
            m_spriteEnemyStatusBase->SetPosition(
                { position.x,position.y + m_kUIPositionCorrectionAmountY }
            );

            m_setUIEnemyPosition = { position.x,position.y };

            m_enemyHPUI->SetUIPosition(m_setUIEnemyPosition);
            //m_enemyBreakUI->SetUIPosition(m_setUIEnemyPosition);
        }
    }
}