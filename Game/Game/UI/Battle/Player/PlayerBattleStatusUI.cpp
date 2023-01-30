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
        const char* m_kSpritePlayerStatusBaseFilePath =
            "Assets/Image/FitnessBar/Player/PlayerStatusBase.png";

        bool CPlayerBattleStatusUI::Start()
        {
            return true;
        }

        void CPlayerBattleStatusUI::LoadLevel(const char* tdlFilePath)
        {
            // プレイヤーのバトルステータスの土台
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                    // プレイヤーステータスの土台部分
                    if (imgData.EqualObjectName(L"プレイヤーステータスの土台部分") == true)
                    {
                        // UIクラスを作成
                        m_spritePlayerStatusBase = NewGO<CSpriteUI>();
                        m_spritePlayerStatusBase->LoadSprite(m_kSpritePlayerStatusBaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spritePlayerStatusBase->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spritePlayerStatusBase->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                });

            // プレイヤーのHPゲージ
            m_playerHPUI = NewGO<CPlayerHPUI>();
            m_playerHPUI->LoadLevel(tdlFilePath);

            // プレイヤーのMPゲージ
            m_playerMPUI = NewGO<CPlayerMPUI>();
            m_playerMPUI->LoadLevel(tdlFilePath);

            // プレイヤーのSPゲージ
            m_playerSPUI = NewGO<CPlayerSPUI>();
            m_playerSPUI->LoadLevel(tdlFilePath);
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
    }
}