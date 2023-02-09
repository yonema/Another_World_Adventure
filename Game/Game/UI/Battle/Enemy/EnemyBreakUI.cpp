#include "YonemaEnginePreCompile.h"
#include "EnemyBreakUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBreakUI::m_kLevel2DFilePath =
            "Assets/Level2D/BreakGauge.tdl";
        
        const char* CEnemyBreakUI::m_kSpriteBreakBarFilePath =
            "Assets/Images/FitnessBar/Enemy/Gauge_Break.png";
        const char* CEnemyBreakUI::m_kSpriteBreakFilePath =
            "Assets/Images/FitnessBar/Enemy/Break_GaugeMax.png";
        const char* CEnemyBreakUI::m_kSpriteBreakReductionFilePath =
            "Assets/Images/FitnessBar/Enemy/Break_GaugeDecrease.png";
        const char* CEnemyBreakUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Enemy/Gauge_Break_Groundwork.png";

        const float CEnemyBreakUI::m_kMaxBarHeightSize = 0.3f;

        bool CEnemyBreakUI::Start()
        {
            return true;
        }

        void CEnemyBreakUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // ブレイクゲージ
                    if ("Gauge_Break" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBreakBar = NewGO<CSpriteUI>();
                        m_spriteBreakBar->LoadSprite(
                            m_kSpriteBreakBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBreakBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UIの初期位置を取得
                        m_initialPositionBreakBar = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // ブレイクゲージがMAXになったときに表示するUI
                    else if ("Break_GaugeMax" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBreak = NewGO<CSpriteUI>();
                        m_spriteBreak->LoadSprite(
                            m_kSpriteBreakFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBreak->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );


                        m_spriteBreak->SetDrawingFlag(false);

                        // UIの初期位置を取得
                        m_initialPositionBreak = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // ブレイクゲージが減少中に表示するUI
                    else if ("Break_GaugeDecrease" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBreakReduction = NewGO<CSpriteUI>();
                        m_spriteBreakReduction->LoadSprite(
                            m_kSpriteBreakReductionFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBreakReduction->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        m_spriteBreakReduction->SetDrawingFlag(false);

                        // UIの初期位置を取得
                        m_initialPositionBreakReduction = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // ブレイクゲージの下地
                    else if ("Gauge_Break_Groundwork" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(
                            m_kSpriteBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UIの初期位置を取得
                        m_initialPositionBase = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
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
            m_spriteBreakBar->SetPosition(position + m_initialPositionBreakBar);
            m_spriteBreak->SetPosition(position + m_initialPositionBreak);
            m_spriteBreakReduction->SetPosition(position + m_initialPositionBreakReduction);
            m_spriteBase->SetPosition(position + m_initialPositionBase);
        }
    }
}