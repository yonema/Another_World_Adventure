#include "YonemaEnginePreCompile.h"
#include "EnemyBreakUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBreakUI::m_kSpriteBreakBarFilePath =
            "Assets/Image/FitnessBar/Enemy/Gauge_Break.png";
        const char* CEnemyBreakUI::m_kSpriteBreakFilePath =
            "Assets/Image/FitnessBar/Enemy/Break_GaugeMax.png";
        const char* CEnemyBreakUI::m_kSpriteBreakReductionFilePath =
            "Assets/Image/FitnessBar/Enemy/Break_GaugeDecrease.png";
        const char* CEnemyBreakUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Enemy/Gauge_Break_Groundwork.png";

        bool CEnemyBreakUI::Start()
        {
            return true;
        }

        void CEnemyBreakUI::LoadLevel(const char* tdlFilePath, const CVector2& basePosition)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // ブレイクゲージ
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBreakBar = NewGO<CSpriteUI>();
                        m_spriteBreakBar->LoadSprite(m_kSpriteBreakBarFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteBreakBar->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBreakBar->SetPivot(imgData.Pivot);

                        // UI位置の補正値を取得
                        m_correctionAmountBreakBar = basePosition - imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの枠
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBreak = NewGO<CSpriteUI>();
                        m_spriteBreak->LoadSprite(m_kSpriteBreakFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteBreak->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBreak->SetPivot(imgData.Pivot);
                        // 非表示にする
                        m_spriteBreak->Deactivate();

                        // UI位置の補正値を取得
                        m_correctionAmountBreak = basePosition - imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの下地
                    if ("" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBreakReduction = NewGO<CSpriteUI>();
                        m_spriteBreakReduction->LoadSprite(m_kSpriteBreakReductionFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteBreakReduction->SetPosition(imgData.Position);
                        // ピボットをロードした画像と同じにする
                        m_spriteBreakReduction->SetPivot(imgData.Pivot);
                        // 非表示にする
                        m_spriteBreakReduction->Deactivate();

                        // UI位置の補正値を取得
                        m_correctionAmountBreakReduction = basePosition - imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーのピンチ時のやつ
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
                });
        }

        void CEnemyBreakUI::OnDestroy()
        {
            DeleteGO(m_spriteBreakBar);
            DeleteGO(m_spriteBreak);
            DeleteGO(m_spriteBreakReduction);
            DeleteGO(m_spriteBase);
        }

        void CEnemyBreakUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // HPバーのアニメーション
            Animation();

        }

        void CEnemyBreakUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            m_spriteBreakBar->SetScale({ 1.0f,m_barPercentage,1.0f });
        }

        void CEnemyBreakUI::SetUIPosition(const CVector2& position)
        {
            m_spriteBreakBar->SetPosition(position + m_correctionAmountBreakBar);
            m_spriteBreak->SetPosition(position + m_correctionAmountBreak);
            m_spriteBreakReduction->SetPosition(position + m_correctionAmountBreakReduction);
            m_spriteBase->SetPosition(position + m_correctionAmountBase);
        }
    }
}