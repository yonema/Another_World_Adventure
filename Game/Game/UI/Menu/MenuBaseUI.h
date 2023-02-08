#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;
        class CMenuSkillWindowUI;
        class COperationMenuSkillUI;

        class CMenuBaseUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CMenuBaseUI() = default;
            ~CMenuBaseUI() = default;

        public:
            void LoadLevel();


        private:
            void Animation(); // UIのアニメーション


        private: // enum
            enum class EnMenu
            {

            };



        private: // constant member
            static const char* m_kLevel2DFilePath;
            static const char* m_kSpriteMenuBaseFilePath;


        private: // data member
            nsLevel2D::CLevel2D m_level;

            // ボタンの画像
            CSpriteUI* m_spriteMenuBase = nullptr;

            CMenuSkillWindowUI* m_menuSkillWindowUI = nullptr;
            COperationMenuSkillUI* m_operationMenuSkillUI = nullptr;
        };
    }
}