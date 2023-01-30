#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
        */
        class CPlayerMPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerMPUI() = default;
            ~CPlayerMPUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UIのアニメーション

        public:
            /**
             * @brief プレイヤーのMPを取得
             * @param mp MP
             * @param maxMP MPの最大値
            */
            void SetUIPlayerMPStatus(const float mp, const float maxMP)
            {
                // 横幅の倍率を計算
                m_barWidthSize = mp / maxMP;
            }

        private:
            static const char* m_kSpriteMPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;

        private: // data member
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spriteMPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地

            float m_barWidthSize = 1.0f; // プレイヤーの体力バーの横幅の倍率

        };
    }
}