#include "YonemaEnginePreCompile.h"
#include "EnemyBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "EnemyHPUI.h"
#include "EnemyBreakUI.h"
#include "../../../Player/PlayerManager.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBattleStatusUI::m_kLevel2DFilePath =
            "Assets/Level2D/EnemyStatus.tdl";

        const char* CEnemyBattleStatusUI::m_kSpriteEnemyStatusBaseFilePath = 
            "Assets/Images/FitnessBar/Enemy/EnemyStatusBase.png";

        const float CEnemyBattleStatusUI::m_kUIPositionCorrectionAmountY = 13.0f;
        const float CEnemyBattleStatusUI::m_kUIPositionCorrectionAmountX = -3.0f;

        const float CEnemyBattleStatusUI::m_kDrawingAngle = 90.0f;

        const float CEnemyBattleStatusUI::m_kEnemyMaximumDistance = 150.0f;


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
                        m_initialPosition = imgData.Position;
                        m_initialScale = imgData.Scale;

                        // フックしたので、trueを返す
                        return true;
                    }

                    return true;
                    return false;
                });

            // 敵のHPゲージ
            m_enemyHPUI = NewGO<CEnemyHPUI>();
            m_enemyHPUI->LoadLevel();

            // 敵のブレイクゲージ
            //m_enemyBreakUI = NewGO<CEnemyBreakUI>();
            //m_enemyBreakUI->LoadLevel();
        }

        void CEnemyBattleStatusUI::OnDestroy()
        {
            DeleteGO(m_spriteEnemyStatusBase);

            DeleteGO(m_enemyHPUI);
            //DeleteGO(m_enemyBreakUI);
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
            if (true == CheckDrawUI(position)) {
                m_spriteEnemyStatusBase->SetDrawingFlag(true);
            }
            else {
                m_spriteEnemyStatusBase->SetDrawingFlag(false);

                return;
            }

            CheckEnemyDistance(position);

            CVector3 targetPosition =
            {
                position.x + m_kUIPositionCorrectionAmountX,
                position.y + m_kUIPositionCorrectionAmountY,
                position.z
            };
            CVector2 uiPosition = MainCamera()->CalcScreenPositionFromWorldPosition(targetPosition);



            // これだと、全部一か所にまとまるので、
            // 補正値を追加で入れること
            m_spriteEnemyStatusBase->SetPosition(
                {
                    uiPosition.x + m_initialPosition.x,
                    uiPosition.y + m_initialPosition.y
                }
            );

            m_setUIEnemyPosition = { uiPosition.x,uiPosition.y };

            m_enemyHPUI->SetUIPosition(m_setUIEnemyPosition);
           // m_enemyBreakUI->SetUIPosition(m_setUIEnemyPosition);
        }

        const bool CEnemyBattleStatusUI::CheckDrawUI(const CVector3& targetPosition)
        {
            CVector3 normalizeCameraForwardDirection = MainCamera()->GetForwardDirection();
            CVector3 normalizeTargetPosition = targetPosition - MainCamera()->GetPosition();

            normalizeCameraForwardDirection.Normalize();
            normalizeTargetPosition.Normalize();

            float resultFieldOfView = 
                nsMath::RadToDeg(std::acos(nsMath::Dot(normalizeCameraForwardDirection, normalizeTargetPosition)));

            // 視野に入っているか計算
            if (resultFieldOfView <= m_kDrawingAngle) {
                // 見つけたので成功
                return true;
            }

            // 失敗
            return false;
        }

        void CEnemyBattleStatusUI::CheckEnemyDistance(const CVector3& targetPosition)
        {
            CVector3 enemyDistance =
                targetPosition - nsPlayer::CPlayerManager::GetInstance()->GetPlayerPosition();

            CVector3 scale = { m_initialScale.x,m_initialScale.y,1.0f };

            float enemyLength = enemyDistance.Length();

            if (m_kEnemyMaximumDistance >= enemyLength) {
                m_spriteEnemyStatusBase->SetDrawingFlag(true);
                m_enemyHPUI->SetAllDrawingFlag(true);
            }
            else {
                m_spriteEnemyStatusBase->SetDrawingFlag(false);
                m_enemyHPUI->SetAllDrawingFlag(false);
            }
            
            return;


            //if (m_kEnemyMaximumDistance >= enemyLength) {
            ////    const float MaxSizeLength = 50.0f;

            ////    const float enemyMinimumDistance = 50.0f;

            ////    if (enemyMinimumDistance >= enemyLength) {
            ////        scale = scale * 1.0f;
            ////        m_spriteEnemyStatusBase->SetScale({ scale.x,scale.y,1.0f });
            ////        m_enemyHPUI->SetAllUIScale({ scale.x,scale.y,1.0f });
            ////        return;
            ////    }



            ////    const float test = 1.0f - (enemyLength - enemyMinimumDistance) / m_kEnemyMaximumDistance;

            ////    if (0.5f < test) {
            ////        scale = scale * test;
            ////        m_spriteEnemyStatusBase->SetScale({ scale.x,scale.y,1.0f });
            ////        m_enemyHPUI->SetAllUIScale({ scale.x,scale.y,1.0f });
            ////    }
            ////    else {
            ////        scale = scale * 0.5f;
            ////        m_spriteEnemyStatusBase->SetScale({ scale.x,scale.y,1.0f });
            ////        m_enemyHPUI->SetAllUIScale({ scale.x,scale.y,1.0f });
            ////    }
            ////}
            ////else {
            ////    m_spriteEnemyStatusBase->SetScale({ 0 ,0 ,1.0f });
            ////    scale = { 0 ,0 ,0 };
            ////    m_enemyHPUI->SetAllUIScale({ scale.x,scale.y,1.0f });
            ////}

    
        }
    }
}