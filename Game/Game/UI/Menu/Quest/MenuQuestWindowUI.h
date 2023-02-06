#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CMenuQuestWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CMenuQuestWindowUI() = default;
            ~CMenuQuestWindowUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);
            /**
             * @brief 受け取ったデータを元に対応した画像を読み込む
             * @param buttonUINum ウィンドウの識別用番号
             * @param imgData レベルデータ
            */
            void LoadWindowSprite(const int windowNum, const nsLevel2D::SLevel2DSpriteData& imgData);

        private:
            void Animation(); // UIのアニメーション


        private: // enum
            enum EnWindowNumber
            {
                enWindow_1,
                enWindow_2,
                enMaxWindowNumber
            };


        private: // constant data member
            static const char* m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber];


        private: // data member
            nsLevel2D::CLevel2D m_level;

            // ボタンの画像
            CSpriteUI* m_spriteWindow[EnWindowNumber::enMaxWindowNumber] = { nullptr };
        };
    }
}