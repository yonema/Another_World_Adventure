#include "YonemaEnginePreCompile.h"
#include "EnemyHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyHPUI::m_kSpriteHPBarFilePath = 
            "Assets/Image/FitnessBar/Common/Bar_HP.png";
        const char* CEnemyHPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CEnemyHPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";
        const char* CEnemyHPUI::m_kSpriteDangerFilePath =
            "Assets/Image/FitnessBar/Common/Bar_HP_Danger.png";

        bool CEnemyHPUI::Start()
        {
            return true;
        }

        void CEnemyHPUI::LoadLevel(const char* tdlFilePath, const CVector2& basePosition)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                //オブジェクトネームが"player_kari"と同じだったら
                    if (imgData.EqualObjectName(L"敵のHPバー") == true)
                    {
                        // UIクラスを作成
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteHPBar->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteHPBar->SetPivot(imgData.pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountHPBar = basePosition - imgData.position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの枠
                    if (imgData.EqualObjectName(L"敵のHPバーの枠") == true)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteFrame->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteFrame->SetPivot(imgData.pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountFrame = basePosition - imgData.position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの下地
                    if (imgData.EqualObjectName(L"敵のHPの下地") == true)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteBase->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBase->SetPivot(imgData.pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountBase = basePosition - imgData.position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーのピンチ時のやつ
                    if (imgData.EqualObjectName(L"敵のHPのピンチ時") == true)
                    {
                        // UIクラスを作成
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite(m_kSpriteDangerFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteDanger->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteDanger->SetPivot(imgData.pivot);
                        // 非表示にする
                        m_spriteDanger->Deactivate();

                        // UI位置の補正値を取得
                        m_correctionAmountDanger = basePosition - imgData.position;

                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CEnemyHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
        }

        void CEnemyHPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // HPバーのアニメーション
            Animation();

        }

        void CEnemyHPUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            m_spriteHPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
        }
    }
}