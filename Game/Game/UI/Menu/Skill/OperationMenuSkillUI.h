#pragma once

namespace nsAWA
{
    namespace nsSkill
    {
        struct SActiveSkillData;
    }

    namespace nsUI
    {
        class CFontArrayUI;
        
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
            void LoadSkillData();

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
            static const int m_kActiveSkillMaxNum = 6;
            static const int m_kPassiveSkillMaxNum = 4;

        private: // data member
            bool m_flagEndProcessing = false;

            std::vector<std::string> m_nowSetSkillName;
            //std::vector<int> m_selectionSetSkill;
            std::vector<std::string> m_selectionSetSkill;

            std::list<nsSkill::SActiveSkillData> m_selectionSetSkillData;
            CFontArrayUI* m_fontSelectionSetSkillName;

            //std::list<std::vector<std::string>> m_selectionSetSkill;

            // スキル選択時のカーソルの位置
            int m_cursorPositionSelectionSetSkill = 0;
        };
    }
}