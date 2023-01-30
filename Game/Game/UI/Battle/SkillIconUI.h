#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        class CSkillIconUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CSkillIconUI() = default;
            ~CSkillIconUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UIのアニメーション


        private: // data member
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spriteBase = nullptr;
            CSpriteUI* m_spriteSkill = nullptr;
        };

    }
}