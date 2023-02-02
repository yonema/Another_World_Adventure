#include "YonemaEnginePreCompile.h"
#include "EnemyHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyHPUI::m_kSpriteHPBarFilePath = 
            "Assets/Images/FitnessBar/Common/Bar_HP.png";
        const char* CEnemyHPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CEnemyHPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";
        const char* CEnemyHPUI::m_kSpriteDangerFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_Danger.png";

        bool CEnemyHPUI::Start()
        {
            return true;
        }

        void CEnemyHPUI::LoadLevel(const char* tdlFilePath, const CVector2& basePosition)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // 敵のHPバー
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteHPBar->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteHPBar->SetPivot(imgData.Pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountHPBar = basePosition - imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの枠
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(m_kSpriteFrameFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteFrame->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteFrame->SetPivot(imgData.Pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountFrame = basePosition - imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの下地
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(m_kSpriteBaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteBase->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBase->SetPivot(imgData.Pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountBase = basePosition - imgData.Position;
                        
                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーのピンチ時のやつ
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite(m_kSpriteDangerFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteDanger->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteDanger->SetPivot(imgData.Pivot);
                        // 非表示にする
                        m_spriteDanger->Deactivate();

                        // UI位置の補正値を取得
                        m_correctionAmountDanger = basePosition - imgData.Position;

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

        void CEnemyHPUI::SetUIPosition(const CVector2& position)
        {
            m_spriteHPBar->SetPosition(position + m_correctionAmountHPBar);
            m_spriteFrame->SetPosition(position + m_correctionAmountFrame);
            m_spriteBase->SetPosition(position + m_correctionAmountBase);
            m_spriteDanger->SetPosition(position + m_correctionAmountDanger);
        }
    }
}