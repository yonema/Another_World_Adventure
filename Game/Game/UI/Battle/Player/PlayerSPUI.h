#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
        */
        class CPlayerSPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerSPUI() = default;
            ~CPlayerSPUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UIのアニメーション

        public:
            /**
             * @brief プレイヤーのSPを取得
             * @param sp SP
             * @param maxSP SPの最大値
            */
            void SetUIPlayerSPStatus(const float sp, const float maxSP)
            {
                // 横幅の倍率を計算
                m_barWidthSize = sp / maxSP;
            }

        private:
            static const char* m_kSpriteSPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;

        private: // data member
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spriteSPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地

            float m_barWidthSize = 1.0f; // プレイヤーの体力バーの横幅の倍率
        };
    }
}