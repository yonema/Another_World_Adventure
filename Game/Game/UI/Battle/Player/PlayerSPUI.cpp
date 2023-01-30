#include "YonemaEnginePreCompile.h"
#include "PlayerSPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerSPUI::m_kSpriteSPBarFilePath =
            "Assets/Image/FitnessBar/Player/Bar_SP.png";
        const char* CPlayerSPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CPlayerSPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";

        bool CPlayerSPUI::Start()
        {
            return true;
        }

        void CPlayerSPUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                //オブジェクトネームが"player_kari"と同じだったら
                    if (imgData.EqualObjectName(L"プレイヤーのSPバー") == true)
                    {
                        // UIクラスを作成
                        m_spriteSPBar = NewGO<CSpriteUI>();
                        m_spriteSPBar->LoadSprite(m_kSpriteSPBarFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteSPBar->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteSPBar->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのSPバーの枠
                    if (imgData.EqualObjectName(L"プレイヤーのSPバーの枠") == true)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteFrame->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteFrame->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのSPバーの下地
                    if (imgData.EqualObjectName(L"プレイヤーのSPの下地") == true)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteBase->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBase->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CPlayerSPUI::OnDestroy()
        {
            DeleteGO(m_spriteSPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
        }

        void CPlayerSPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // SPバーのアニメーション
            Animation();

        }

        void CPlayerSPUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            m_spriteSPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}