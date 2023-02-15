#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CGuildQuestText;

        class CGuildWindowUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

            bool IsEnd()
            {
                return m_endFlag;
            }
        public:
            CGuildWindowUI() = default;
            ~CGuildWindowUI() = default;

        private:
            void InitQuests();

            void SelectUp();

            void SelectDown();

            void SelectOK();
        private: // enum
            enum EnWindowNumber
            {
                enWindow_1,
                enWindow_2,
                enMaxWindowNumber
            };


        private: // constant data member
            const char* m_kGuildWindowFilePath = "Assets/Level2D/LevelFiles/InnUI.tdl"; //‰¼
            const CVector2 m_kTextStandardPosition = CVector2(-480.0f, -200.0f);
            const CVector2 m_kCursorStandardPosition = CVector2(-500.0f, -200.0f);
            const float m_kOffset = 75;
            const float m_kWaitTime = 0.16f;

        private: // data member
            nsLevel2D::CLevel2D m_level;
            bool m_playingAnimation = false;
            bool m_isInputDisable = false;
            float m_disableTime = 0.0f;
            std::vector<CGuildQuestText*> m_showQuests;
            bool m_endFlag = false;
            CSpriteRenderer* m_cursorRenderer = nullptr;
            int m_selectingIndex = 0;
        };
    }
}