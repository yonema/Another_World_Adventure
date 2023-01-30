#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
        */
        class CEnemyBreakUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CEnemyBreakUI() = default;
            ~CEnemyBreakUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath, const CVector2& basePosition);

        private:
            void Animation(); // UIのアニメーション

        public:
            /**
             * @brief ブレイクゲージの量を取得
             * @param breakBar ブレイクゲージの量
            */
            void SetUIEnemyBreakStatus(const float breakBar)
            {
                // 横幅の倍率を計算
                m_barPercentage = breakBar / 100;
            }
            /**
             * @brief UIの位置を取得
             * @param position 敵の位置
            */
            void SetUIPosition(const CVector2& position)
            {
                m_spriteBreakBar->SetPosition(position + m_correctionAmountBreakBar);
                m_spriteBreak->SetPosition(position + m_correctionAmountBreak);
                m_spriteBreakReduction->SetPosition(position + m_correctionAmountBreakReduction);
                m_spriteBase->SetPosition(position + m_correctionAmountBase);
            }

        private:
            static const char* m_kSpriteBreakBarFilePath;
            static const char* m_kSpriteBreakFilePath;
            static const char* m_kSpriteBreakReductionFilePath;
            static const char* m_kSpriteBaseFilePath;

        private: // data member
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spriteBreakBar = nullptr; // ブレイクゲージ
            CSpriteUI* m_spriteBreak = nullptr; // ブレイク時のBreak!
            CSpriteUI* m_spriteBreakReduction = nullptr; // ブレイクゲージ減少中のBreak!
            CSpriteUI* m_spriteBase = nullptr; // ブレイクゲージの下地

            // UIの位置の補正値
            CVector2 m_correctionAmountBreakBar = CVector2::Zero();
            CVector2 m_correctionAmountBreak = CVector2::Zero();
            CVector2 m_correctionAmountBreakReduction = CVector2::Zero();
            CVector2 m_correctionAmountBase = CVector2::Zero();

            float m_barPercentage = 0.0f; // ブレイクゲージの割合

        };
    }
}