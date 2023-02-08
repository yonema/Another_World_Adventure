#include "YonemaEnginePreCompile.h"
#include "EnemyHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyHPUI::m_kLevel2DFilePath =
            "Assets/Level2D/EnemyHPBar.tdl";

        const char* CEnemyHPUI::m_kSpriteHPBarFilePath = 
            "Assets/Images/FitnessBar/Common/Bar_HP.png";
        const char* CEnemyHPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CEnemyHPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";
        const char* CEnemyHPUI::m_kSpriteDangerFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_Danger.png";
        const char* CEnemyHPUI::m_kSpriteDecreaaseFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_DecreaseAnimation.png";

        const float CEnemyHPUI::m_kMaxBarWidthSize = 0.3f;

        const float CEnemyHPUI::m_kDangerLine = 0.3f * m_kMaxBarWidthSize;

        const float CEnemyHPUI::m_kStartDecreaseBarAnimationTime = 5.0f;
        const float CEnemyHPUI::m_kStartDecreaseBarAnimationTimeAmount = 0.1f;
        // 減少アニメーションの減少量
        const float CEnemyHPUI::m_kDecreaseBarDecreaseAmount = 0.005f;

        bool CEnemyHPUI::Start()
        {
            return true;
        }

        void CEnemyHPUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // 敵のHPバー
                    if ("Bar_HP" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(
                            m_kSpriteHPBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteHPBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UIの初期位置を取得
                        m_initialPositionHPBar = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの枠
                    else if ("BarFrame" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(
                            m_kSpriteFrameFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteFrame->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UIの初期位置を取得
                        m_initialPositionFrame = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // 敵のHPバーの下地
                    else if ("BarGroundwork" == imgData.Name)
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
                    // 敵のHPバーのピンチ時のやつ
                    else if ("Bar_HP_Danger" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteDanger = NewGO<CSpriteUI>();
                        m_spriteDanger->LoadSprite(
                            m_kSpriteDangerFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteDanger->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );
                        // 非表示にする
                        m_spriteDanger->SetDrawingFlag(false);

                        // UIの初期位置を取得
                        m_initialPositionDanger = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }
                    // HPバーのディレイアニメーション用のUI
                    else if ("Bar_HP_DecreaseAnimation" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteDecrease = NewGO<CSpriteUI>();
                        m_spriteDecrease->LoadSprite(
                            m_kSpriteDecreaaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteDecrease->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UIの初期位置を取得
                        m_initialPositionDecrease = imgData.Position;

                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });
        }

        void CEnemyHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
            DeleteGO(m_spriteDecrease);
        }

        void CEnemyHPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // HPバーのアニメーション
            Animation();

        }

        void CEnemyHPUI::Animation()
        {
            // 遅れて減少するゲージのアニメーション
            DecreaseBarAnimation();

            // HPが３割を切っているかを確認
            ChangeDangerUI();


            // ゲージの長さ（横幅）を適用
            m_spriteHPBar->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
            m_spriteDanger->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
            m_spriteDecrease->SetScale({ m_decreaseBarWidthSize,m_kMaxBarWidthSize,1.0f });

            // 現在のバーの横幅を保存
            m_oldBarWidthSize = m_barWidthSize;
        }

        void CEnemyHPUI::ChangeDangerUI()
        {
            // ピンチ状態のとき
            if (m_kDangerLine > m_barWidthSize) {
                // ピンチ状態のUIが非表示なら
                if (false == m_spriteDanger->IsDrawingFlag()) {
                    m_spriteDanger->SetDrawingFlag(true);
                    m_spriteHPBar->SetDrawingFlag(false);
                }
            }
            // ピンチ状態ではないとき
            else {
                // ピンチ状態のUIが表示状態なら
                if (true == m_spriteDanger->IsDrawingFlag()) {
                    m_spriteDanger->SetDrawingFlag(false);
                    m_spriteHPBar->SetDrawingFlag(true);
                }
            }
        }

        const bool CEnemyHPUI::StartDecreaseBarAnimationTimer()
        {
            // タイマーが設定時間を超えたか
            if (m_kStartDecreaseBarAnimationTime <= m_startDecreaseBarAnimationTimer) {
                return true;
            }

            // タイマーを進める
            m_startDecreaseBarAnimationTimer += m_kStartDecreaseBarAnimationTimeAmount;

            return false;
        }

        void CEnemyHPUI::DecreaseBarAnimation()
        {
            // アニメーションバーがHPバーより短い場合
            if (m_decreaseBarWidthSize <= m_barWidthSize) {
                m_decreaseBarWidthSize = m_barWidthSize;
                return;
            }

            // アニメーションを始めるまでのタイマー処理
            if (false == StartDecreaseBarAnimationTimer()) {
                return;
            }

            // アニメーションバーがHPバーに徐々に近づくアニメーション
            m_decreaseBarWidthSize -= m_kDecreaseBarDecreaseAmount;
        }

        void CEnemyHPUI::SetUIPosition(const CVector2& position)
        {
            m_spriteHPBar->SetPosition(position + m_initialPositionHPBar);
            m_spriteFrame->SetPosition(position + m_initialPositionFrame);
            m_spriteBase->SetPosition(position + m_initialPositionBase);
            m_spriteDanger->SetPosition(position + m_initialPositionDanger);
            m_spriteDecrease->SetPosition(position + m_initialPositionDecrease);
        }
    }
}