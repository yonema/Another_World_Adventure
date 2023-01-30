#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
        */
        class CItemUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CItemUI() = default;
            ~CItemUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UIのアニメーション

        public:
            /**
             * @brief プレイヤーのHPを
             * @param hp 体力
             * @param maxHP 体力の最大値
            */
            void SetUIPlayerMPStatus(const float& mp, const float& maxMP)
            {
                // 横幅の倍率を計算
                m_barWidthSize = mp / maxMP;
            }

        private: // data member
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spriteBase = nullptr; // HPバー


            float m_barWidthSize = 1.0f; // プレイヤーの体力バーの横幅の倍率

        };
    }
}