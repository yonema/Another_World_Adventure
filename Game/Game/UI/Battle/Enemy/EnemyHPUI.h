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
            void LoadLevel(const CVector2& basePosition);

        private:
            void Animation(); // UIのアニメーション


            void ChangeDangerUI(const bool flagDanger);

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

                if (m_oldDecreaseBarWidthSize != m_barWidthSize) {
                    m_startDecreaseBarAnimationTimer = 0;
                }
            }
            /**
             * @brief UIの位置を取得
             * @param position 敵の位置
            */
            void SetUIPosition(const CVector2& position);

        private:
            static const char* m_kSpriteHPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;
            static const char* m_kSpriteDangerFilePath;
            static const char* m_kSpriteDecreaaseFilePath;

            static const char* m_kLevel2DFilePath;

            static const float m_kMaxBarWidthSize;

            static const float m_kDangerLine;


            static const float m_kStartDecreaseBarAnimationTime;
            static const float m_kStartDecreaseBarAnimationTimeAmount;
            // 減少アニメーションの減少量
            static const float m_kDecreaseBarDecreaseAmount;



        private: // data member
            // 実装されたら、下のやつを追加
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteHPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地
            CSpriteUI* m_spriteDanger = nullptr; // ピンチ時のHPバー
            CSpriteUI* m_spriteDecrease = nullptr; // HPバーのディレイアニメーションバー

            // UIの位置の補正値
            CVector2 m_initialPositionHPBar = CVector2::Zero();
            CVector2 m_initialPositionFrame = CVector2::Zero();
            CVector2 m_initialPositionBase = CVector2::Zero();
            CVector2 m_initialPositionDanger = CVector2::Zero();
            CVector2 m_initialPositionDecrease = CVector2::Zero();

            float m_barWidthSize = m_kMaxBarWidthSize; // プレイヤーの体力バーの横幅の倍率

            float m_decreaseBarWidthSize = m_kMaxBarWidthSize; // あとから追って減るゲージの横幅の倍率
            float m_startDecreaseBarAnimationTimer = 0.0f; // あとから追ってゲージが減るアニメーションのタイマー

            float m_oldDecreaseBarWidthSize = m_kMaxBarWidthSize; // ゲージが減少する前の横幅の倍率


        };
    }
}