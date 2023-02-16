#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
        */
        class CEnemyHPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CEnemyHPUI() = default;
            ~CEnemyHPUI() = default;

        public:
            void LoadLevel();

        private:
            void Animation(); // UIのアニメーション


            void ChangeDangerUI();

            const bool StartDecreaseBarAnimationTimer();

            /**
             * @brief 遅れて減少するゲージのアニメーション
            */
            void DecreaseBarAnimation();

        public:
            /**
             * @brief UIに必要な敵の体力の情報を取得
             * @param hp 体力
             * @param maxHP 体力の最大値
            */
            void SetUIEnemyHPStatus(const float hp, const float maxHP)
            {
                // 横幅の倍率を計算
                m_barWidthSize = hp / maxHP * m_kMaxBarWidthSize;

                if (m_oldBarWidthSize != m_barWidthSize) {
                    m_startDecreaseBarAnimationTimer = 0;
                }
            }
            /**
             * @brief UIの位置を取得
             * @param position 敵の位置
            */
            void SetUIPosition(const CVector2& position);

            void SetAllUIScale(const CVector3& scale)
            {
                m_distanceScale = scale;
            }

            void SetAllDrawingFlag(const bool flag)
            {
                m_flagAllDrawSprite = flag;
            }

        private:
            ////////////////////////////////////////////////////////////
            // ファイルパス
            ////////////////////////////////////////////////////////////

            static const char* m_kLevel2DFilePath;

            static const char* m_kSpriteHPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;
            static const char* m_kSpriteDangerFilePath;
            static const char* m_kSpriteDecreaaseFilePath;

            ////////////////////////////////////////////////////////////
            // ステータス系
            ////////////////////////////////////////////////////////////

            static const float m_kMaxBarWidthSize; // UIの最大の横幅

            static const float m_kDangerLine; // ピンチ判定のライン


            static const float m_kStartDecreaseBarAnimationTime; // 減少アニメーションの始まるまでの時間
            static const float m_kStartDecreaseBarAnimationTimeAmount; // 減少アニメーションの始まるまでのカウント時間
            static const float m_kDecreaseBarDecreaseAmount; // 減少アニメーションの減少量



        private: // data member
            ////////////////////////////////////////////////////////////
            // レベル、画像
            ////////////////////////////////////////////////////////////
            nsLevel2D::CLevel2D m_level; // レベルファイルクラス

            CSpriteUI* m_spriteHPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地
            CSpriteUI* m_spriteDanger = nullptr; // ピンチ時のHPバー
            CSpriteUI* m_spriteDecrease = nullptr; // HPバーのディレイアニメーションバー

            ////////////////////////////////////////////////////////////
            // ステータス
            ////////////////////////////////////////////////////////////

            // UIの初期位置
            CVector2 m_initialPositionHPBar = CVector2::Zero();
            CVector2 m_initialPositionFrame = CVector2::Zero();
            CVector2 m_initialPositionBase = CVector2::Zero();
            CVector2 m_initialPositionDanger = CVector2::Zero();
            CVector2 m_initialPositionDecrease = CVector2::Zero();

            CVector3 m_distanceScale = CVector3::One();

            float m_barWidthSize = m_kMaxBarWidthSize; // プレイヤーの体力バーの横幅の倍率

            float m_decreaseBarWidthSize = m_kMaxBarWidthSize; // あとから追って減るゲージの横幅の倍率
            float m_startDecreaseBarAnimationTimer = 0.0f; // あとから追ってゲージが減るアニメーションのタイマー

            float m_oldBarWidthSize = m_kMaxBarWidthSize; // ゲージが減少する前の横幅の倍率

            bool m_flagAllDrawSprite = true;
        };
    }
}