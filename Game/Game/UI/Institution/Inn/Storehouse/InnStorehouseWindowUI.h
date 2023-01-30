#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CInnStorehouseWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CInnStorehouseWindowUI() = default;
            ~CInnStorehouseWindowUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);
            /**
             * @brief 受け取ったデータを元に対応した画像を読み込む
             * @param buttonUINum ウィンドウの識別用番号
             * @param imgData レベルデータ
            */
            void LoadWindowSprite(const int windowNum, LevelObjectData& imgData);

        private:
            void Animation(); // UIのアニメーション


        private: // enum
            static enum EnWindowNumber
            {
                enWindow_1,
                enWindow_2,
                enWindow_3,
                enWindow_4,
                enMaxWindowNumber
            };


        private: // constant data member
            static const char* m_kSpriteWindowFilePath[EnWindowNumber::enMaxWindowNumber];


        private: // data member
            // ボタンの画像
            CSpriteUI* m_spriteWindow[EnWindowNumber::enMaxWindowNumber] = { nullptr };
        };
    }
}