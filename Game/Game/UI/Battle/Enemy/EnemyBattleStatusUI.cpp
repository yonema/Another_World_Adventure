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
            "Assets/Image/FitnessBar/Enemy/EnemyStatusBase.png";

        bool CEnemyBattleStatusUI::Start()
        {
            return true;
        }

        void CEnemyBattleStatusUI::LoadLevel(const char* tdlFilePath)
        {
            // プレイヤーのバトルステータスの土台
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // 敵ステータスの土台部分
                    if (imgData.EqualObjectName(L"プレイヤーステータスの土台部分") == true)
                    {
                        // UIクラスを作成
                        m_spriteEnemyStatusBase = NewGO<CSpriteUI>();
                        m_spriteEnemyStatusBase->LoadSprite(m_kSpriteEnemyStatusBaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteEnemyStatusBase->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteEnemyStatusBase->SetPivot(imgData.pivot);

                        // 土台部分以外のUIの位置の基準になる位置を取得
                        m_basePosition = imgData.position;

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
    }
}