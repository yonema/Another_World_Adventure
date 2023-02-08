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
            void LoadLevel();

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
                m_barWidthSize = mp / maxMP * m_kMaxBarWidthSize;
            }

        private:
            static const char* m_kSpriteMPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;

            static const char* m_kLevel2DFilePath;

            static const float m_kMaxBarWidthSize;


        private: // data member
            // 実装されたら、下のやつを追加
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteMPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地

            float m_barWidthSize = m_kMaxBarWidthSize; // プレイヤーの体力バーの横幅の倍率

        };
    }
}