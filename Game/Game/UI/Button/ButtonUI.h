#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CButtonUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CButtonUI() = default;
            ~CButtonUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);
            /**
             * @brief 受け取ったデータを元に対応した画像を読み込む
             * @param buttonUINum ボタンの画像の識別用番号
             * @param imgData レベルデータ
            */
            void LoadButtonSprite(const int buttonUINum, const nsLevel2D::SLevel2DSpriteData& imgData);

        private:
            void Animation(); // UIのアニメーション


        public: // enum
            // ボタンの画像識別用の列挙型
            enum EnButtonUI
            {
                enA,
                enB,
                enX,
                enY,
                enBL,
                enBR,
                enTL,
                enTR,
                enMaxButtonUI
            };


        private: // constant data member
            // ボタンの画像のファイルパス
            static const char* m_kSpriteButtonFilePath[EnButtonUI::enMaxButtonUI];
           
            
        private: // data member
            nsLevel2D::CLevel2D m_level;

            // ボタンの画像
            CSpriteUI* m_spriteButton = nullptr;
        };
    }
}