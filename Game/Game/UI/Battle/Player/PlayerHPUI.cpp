#include "YonemaEnginePreCompile.h"
#include "PlayerHPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerHPUI::m_kSpriteHPBarFilePath =
            "Assets/Image/FitnessBar/Common/Bar_HP.png";
        const char* CPlayerHPUI::m_kSpriteFrameFilePath =
            "Assets/Image/FitnessBar/Common/BarFrame.png";
        const char* CPlayerHPUI::m_kSpriteBaseFilePath =
            "Assets/Image/FitnessBar/Common/BarGroundwork.png";
        const char* CPlayerHPUI::m_kSpriteDangerFilePath =
            "Assets/Image/FitnessBar/Common/Bar_HP_Danger.png";
        const char* CPlayerHPUI::m_kSpriteDecreaaseFilePath =
            "ファイルパス";

        // ピンチ判定ライン
        const float CPlayerHPUI::m_kDangerLine = 0.3f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTime = 1.0f;
        const float CPlayerHPUI::m_kStartDecreaseBarAnimationTimeAmount = 0.1f;
        // 減少アニメーションの減少量
        const float CPlayerHPUI::m_kDecreaseBarDecreaseAmount = 0.01f;

        bool CPlayerHPUI::Start()
        {
            return true;
        }

        void CPlayerHPUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                //オブジェクトネームが"player_kari"と同じだったら
                    if (imgData.EqualObjectName(L"プレイヤーのHPバー") == true)
                    {
                        // UIクラスを作成
                        m_spriteHPBar = NewGO<CSpriteUI>();
                        m_spriteHPBar->LoadSprite(m_kSpriteHPBarFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteHPBar->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteHPBar->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのHPバーの枠
                    if (imgData.EqualObjectName(L"プレイヤーのHPバーの枠") == true)
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
                    // プレイヤーのHPバーの下地
                    if (imgData.EqualObjectName(L"プレイヤーのHPの下地") == true)
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
                    // プレイヤーのHPバーのピンチ時のやつ
                    if (imgData.EqualObjectName(L"プレイヤーのHPのピンチ時") == true)
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
                        // フックしたので、trueを返す
                        return true;
                    }
                    // HPバーのディレイアニメーション用のUI
                    if (imgData.EqualObjectName(L"文字列") == true)
                    {
                        // UIクラスを作成
                        m_spriteDecrease = NewGO<CSpriteUI>();
                        m_spriteDecrease->LoadSprite(m_kSpriteDecreaaseFilePath);
                        // ポジションをロードした画像と同じにする
                        m_spriteDecrease->SetPosition(imgData.position);
                        // ピボットをロードした画像と同じにする
                        m_spriteDecrease->SetPivot(imgData.pivot);
                        // フックしたので、trueを返す
                        return true;
                    }
                });
        }

        void CPlayerHPUI::OnDestroy()
        {
            DeleteGO(m_spriteHPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteDanger);
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
            if (m_kDangerLine > m_barWidthSize) {
                ChangeDangerUI(true);
            }
            else {
                ChangeDangerUI(false);
            }

            // ゲージの長さ（横幅）を適用
            m_spriteHPBar->SetScale({ m_barWidthSize,1.0f,1.0f });
            m_spriteDanger->SetScale({ m_barWidthSize,1.0f,1.0f });
            m_spriteDecrease->SetScale({ m_decreaseBarWidthSize,1.0f,1.0f });

            m_oldDecreaseBarWidthSize = m_decreaseBarWidthSize;
        }

        void CPlayerHPUI::ChangeDangerUI(const bool flagDanger)
        {
            // ピンチ状態のとき
            if (true == flagDanger) {
                // ピンチ状態のUIが非表示なら
                if (false == m_spriteDanger->IsActive()) {
                    m_spriteDanger->Activate();
                    m_spriteHPBar->Deactivate();
                }
            }
            // ピンチ状態ではないとき
            else {
                // ピンチ状態のUIが表示状態なら
                if (true == m_spriteDanger->IsActive()) {
                    m_spriteDanger->Deactivate();
                    m_spriteHPBar->Activate();
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
            // 古い情報がリアルタイムのより少ない場合
            if (m_decreaseBarWidthSize <= m_barWidthSize) {
                m_decreaseBarWidthSize = m_barWidthSize;
                return;
            }

            // アニメーションを始めるまでのタイマー
            if (false == StartDecreaseBarAnimationTimer()) {
                return;
            }

            // 古いバーがリアルタイムのバーに徐々に近づくアニメーション
            // ※アニメーション速度は速めで！
            m_decreaseBarWidthSize -= m_kDecreaseBarDecreaseAmount;
        }
    }
}