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
            void LoadLevel();

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
            void SetUIPosition(const CVector2& position);

        private:
            static const char* m_kSpriteBreakBarFilePath;
            static const char* m_kSpriteBreakFilePath;
            static const char* m_kSpriteBreakReductionFilePath;
            static const char* m_kSpriteBaseFilePath;

            static const char* m_kLevel2DFilePath;

        private: // data member
            // 実装されたら、下のやつを追加
            nsLevel2D::CLevel2D m_level;

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