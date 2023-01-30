#include "YonemaEnginePreCompile.h"
#include "PlayerMPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerMPUI::m_kSpriteMPBarFilePath = 
            "Assets/Image/FitnessBar/Player/Bar_MP.png";
        const char* CPlayerMPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CPlayerMPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";

        bool CPlayerMPUI::Start()
        {
            return true;
        }

        void CPlayerMPUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                //オブジェクトネームが"player_kari"と同じだったら
                    if (imgData.EqualObjectName(L"プレイヤーのMPバー") == true)
                    {
                        // UIクラスを作成
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteMPBar->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteMPBar->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのMPバーの枠
                    if (imgData.EqualObjectName(L"プレイヤーのMPバーの枠") == true)
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
                    // プレイヤーのMPバーの下地
                    if (imgData.EqualObjectName(L"プレイヤーのMPの下地") == true)
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

        void CPlayerMPUI::OnDestroy()
        {
            DeleteGO(m_spriteMPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
        }

        void CPlayerMPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // MPバーのアニメーション
            Animation();

        }

        void CPlayerMPUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            m_spriteMPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}