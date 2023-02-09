#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CSkillIconUI : public IGameObject
        {
        private:
            enum class EnSkillButton
            {
                enSkill_A,
                enSkill_B,
                enSkill_X,
                enSkill_Y,
                enSkill_RB,
                enSkill_RT,
                enMaxSkillButton
            };


        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CSkillIconUI() = default;
            ~CSkillIconUI() = default;

        public:
            void LoadLevel();

            /**
             * @brief 受け取ったデータを元に対応した画像を読み込む
             * @param buttonUINum ウィンドウの識別用番号
             * @param imgData レベルデータ
            */
            void LoadSkillIconSprite(const EnSkillButton& skillNum, const nsLevel2D::SLevel2DSpriteData& imgData);

        private:
            void Animation(); // UIのアニメーション



        public:
            void ActiveDrawing();

            void DeactiveDrawing();


        private: // constant member
            static const char* m_kLevel2DFilePath;

            static const char* m_kSkillIconFilePath;
            static const char* m_kFireFilePath;


        private: // data member
            // 実装されたら、下のやつを追加
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteSkillIcon[static_cast<int>(EnSkillButton::enMaxSkillButton)] = { nullptr };

            //CSpriteUI* m_spriteBase = nullptr;
            //CSpriteUI* m_spriteSkill = nullptr;
        };

    }
}