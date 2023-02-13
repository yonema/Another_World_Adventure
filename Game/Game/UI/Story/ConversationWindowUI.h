#pragma once
#include "ConversationTextUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        class CConversationWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

            /**
             * @brief 会話のCSVファイルをセット　必ず呼ぶこと。
             * @param csvFilePath 会話のCSVファイルパス
            */
            void InitConvesationCSV(const wchar_t* csvFilePath)
            {
                m_text.Init(csvFilePath);
            }

            constexpr bool IsEnd() const noexcept
            {
                return m_endFlag;
            }

        public:
            CConversationWindowUI() = default;
            ~CConversationWindowUI() = default;
        private: // constant data member
            const char* m_kSpriteWindowFilePath = "Assets/Level2D/LevelFiles/ConversationWindow.tdl";
        private: // data member
            nsLevel2D::CLevel2D m_level;    //会話ウィンドウのレベル
            CConversationTextUI m_text;     //会話テキストの表示クラス
            bool m_endFlag = false;
        };
    }
}