#include "YonemaEnginePreCompile.h"
#include "EnemyBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "EnemyHPUI.h"
#include "EnemyBreakUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBattleStatusUI::m_kSpriteEnemyStatusBaseFilePath = 
            "Assets/Images/FitnessBar/Enemy/EnemyStatusBase.png";

        bool CEnemyBattleStatusUI::Start()
        {
            return true;
        }

        void CEnemyBattleStatusUI::LoadLevel(const char* tdlFilePath)
        {
            // プレイヤーのバトルステータスの土台
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // 敵ステータスの土台部分
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteEnemyStatusBase = NewGO<CSpriteUI>();
                        m_spriteEnemyStatusBase->LoadSprite(m_kSpriteEnemyStatusBaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteEnemyStatusBase->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteEnemyStatusBase->SetPivot(imgData.Pivot);

                        // 土台部分以外のUIの位置の基準になる位置を取得
                        m_basePosition = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                });

            // 敵のHPゲージ
            m_enemyHPUI = NewGO<CEnemyHPUI>();
            m_enemyHPUI->LoadLevel(tdlFilePath, m_basePosition);

            // 敵のブレイクゲージ
            m_enemyBreakUI = NewGO<CEnemyBreakUI>();
            m_enemyBreakUI->LoadLevel(tdlFilePath, m_basePosition);
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
            m_enemyBreakUI->SetUIEnemyBreakStatus(breakBar);
        }

        void CEnemyBattleStatusUI::SetUIEnemyPosition(const CVector2& position)
        {
            // これだと、全部一か所にまとまるので、
            // 補正値を追加で入れること
            m_spriteEnemyStatusBase->SetPosition(
                { position.x,position.y + m_kUIPositionCorrectionAmountY }
            );

            m_enemyHPUI->SetUIPosition(position);
            m_enemyBreakUI->SetUIPosition(position);
        }
    }
}