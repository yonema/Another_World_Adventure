#include "YonemaEnginePreCompile.h"
#include "PlayerHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerHPUI::m_kLevel2DFilePath =
            "Assets/Level2D/HP_Bar.tdl";

        const char* CPlayerHPUI::m_kSpriteHPBarFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP.png";
        const char* CPlayerHPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CPlayerHPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";
        const char* CPlayerHPUI::m_kSpriteDangerFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_Danger.png";
        const char* CPlayerHPUI::m_kSpriteDecreaaseFilePath =
            "Assets/Images/FitnessBar/Common/Bar_HP_DecreaseAnimation.png";

        const float CPlayerHPUI::m_kMaxBarWidthSize = 0.5f;
        const float CPlayerHPUI::m_kDangerLine = 0.3f * m_kMaxBarWidthSize;

        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTime = 5.0f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTimeAmount = 0.1f;
        const float CPlayerHPUI::m_kDecreaseBarDecreaseAmount = 0.005f;



        bool CPlayerHPUI::Start()
        {
            return true;
        }

        void CPlayerHPUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // プレイヤーのHPバー
                    if ("HP_Bar" == imgData.Name)
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

                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの枠
                    else if ("HP_BarFrame" == imgData.Name)
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

                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの下地
                    else if ("HP_BarGroundwork" == imgData.Name)
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

                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーのピンチ時のやつ
                    else if ("HP_DangerBar" == imgData.Name)
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
                        // フックしたので、trueを返す
                        return true;
                    }
                    // HPバーのディレイアニメーション用のUI
                    else if ("HP_DecreaseAnimationBar" == imgData.Name)
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

                        // フックしたので、trueを返す
                        return true;
                    }

                    return false;
                });
        }

        void CPlayerHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
            DeleteGO(m_spriteDecrease);
        }

        void CPlayerHPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // HPバーのアニメーション
            Animation();

        }

        void CPlayerHPUI::Animation()
        {
            // 遅れて減少するゲージのアニメーション
            DecreaseBarAnimation();

            // HPが３割を切っているかを確認
            ChangeDangerUI();


            // ゲージの長さ（横幅）を適用
            m_spriteHPBar->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
            m_spriteDanger->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
            m_spriteDecrease->SetScale({ m_decreaseBarWidthSize,m_kMaxBarWidthSize,1.0f });

            // 現在のバーの情報を保存
            m_oldBarWidthSize = m_barWidthSize;
        }

        void CPlayerHPUI::ChangeDangerUI()
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

        const bool CPlayerHPUI::StartDecreaseBarAnimationTimer()
        {
            // タイマーが設定時間を超えたか
            if (m_kStartDecreaseBarAnimationTime <= m_startDecreaseBarAnimationTimer) {
                return true;
            }

            // タイマーを進める
            m_startDecreaseBarAnimationTimer += m_kStartDecreaseBarAnimationTimeAmount;

            return false;
        }

        void CPlayerHPUI::DecreaseBarAnimation()
        {
            // アニメーションバーがHPバーより短い場合
            if (m_decreaseBarWidthSize <= m_barWidthSize) {
                m_decreaseBarWidthSize = m_barWidthSize;
                return;
            }

            // アニメーションを始めるまでのタイマー
            if (false == StartDecreaseBarAnimationTimer()) {
                return;
            }

            // 古いバーがリアルタイムのバーに徐々に近づくアニメーション
            m_decreaseBarWidthSize -= m_kDecreaseBarDecreaseAmount;
        }
    }
}