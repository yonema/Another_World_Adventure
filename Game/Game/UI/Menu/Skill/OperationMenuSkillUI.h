#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class COperationMenuSkillUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            COperationMenuSkillUI() = default;
            ~COperationMenuSkillUI() = default;

        private:
            void Animation(); // UIのアニメーション

        private:
            void LoadNowSetSkill();

            void LoadSelectionSetSkill();

        private:
            void OperationActiveOrPassive();

            void OperationNowSetSkill();

            void OperationSelectionSetSkill();

        private:
            void ChangeSetSkill();


        public:
            const bool GetFlagEndProcessing() const
            {
                return m_flagEndProcessing;
            }


        private: // enum
            /**
             * @brief アクティブかパッシブか
            */
            enum class EnActiveOrPassive
            {
                enActive,
                enPassive,
                enMaxEn
            };
            EnActiveOrPassive m_activeOrPassive = EnActiveOrPassive::enActive;

            enum class EnNowSetSkillFrame
            {
                en1_A,
                en2_B,
                en3_X,
                en4_Y,
                en5_RB,
                en6_RT,
                enMaxEn
            };
            EnNowSetSkillFrame m_nowSetSkillFrame = EnNowSetSkillFrame::en1_A;

            enum class EnWindowStatus
            {
                enActiveOrPassive,
                enNowSetSkill,
                enSelectionSetSkill,
                enMaxEn
            };
            EnWindowStatus m_windowStatus = EnWindowStatus::enActiveOrPassive;


        private: // constant data member


        private: // data member
            bool m_flagEndProcessing = false;

            std::vector<int> m_nowSetSkill;
            std::vector<int> m_selectionSetSkill;

            // スキル選択時のカーソルの位置
            int m_cursorPositionSelectionSetSkill = 0;
        };
    }
}