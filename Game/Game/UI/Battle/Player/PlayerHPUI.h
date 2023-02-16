#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
        */
        class CPlayerHPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerHPUI() = default;
            ~CPlayerHPUI() = default;

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
             * @brief UIに必要なプレイヤーの体力の情報を取得
             * @param hp 体力
             * @param maxHP 体力の最大値
            */
            void SetUIPlayerHPStatus(const float hp, const float maxHP)
            {
                // 横幅の倍率を計算
                m_barWidthSize = hp / maxHP * m_kMaxBarWidthSize;

                if (m_oldBarWidthSize != m_barWidthSize) {
                    m_startDecreaseBarAnimationTimer = 0;
                }
            }

            void ActivatePlayerBattleStatusDrawingFlag();

            void DeactivatePlayerBattleStatusDrawingFlag();

        private: // constant member
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

            static const float m_kMaxBarWidthSize; // バーの横幅の最大値
            static const float m_kDangerLine; // ピンチ判定ライン

            static const float m_kStartDecreaseBarAnimationTime; // アニメーションが始まるまでの時間
            static const float m_kStartDecreaseBarAnimationTimeAmount; // アニメーションが始まるまでのタイマーの進む量
            static const float m_kDecreaseBarDecreaseAmount; // アニメーションバーの減少量


        private: // data member
            ////////////////////////////////////////////////////////////
            // レベル、画像
            ////////////////////////////////////////////////////////////
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteHPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地
            CSpriteUI* m_spriteDanger = nullptr; // ピンチ時のHPバー
            CSpriteUI* m_spriteDecrease = nullptr; // HPバーのディレイアニメーションバー

            ////////////////////////////////////////////////////////////
            // ステータス
            ////////////////////////////////////////////////////////////

            float m_barWidthSize = m_kMaxBarWidthSize; // プレイヤーの体力バーの横幅の倍率
            float m_decreaseBarWidthSize = m_kMaxBarWidthSize; // あとから追って減るゲージの横幅の倍率
            float m_startDecreaseBarAnimationTimer = 0.0f; // あとから追ってゲージが減るアニメーションのタイマー

            float m_oldBarWidthSize = m_kMaxBarWidthSize; // ゲージが減少する前の横幅の倍率
        };
    }
}