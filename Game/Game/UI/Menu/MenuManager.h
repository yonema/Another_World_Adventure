#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CMenuBaseUI;

        class CMenuManager : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CMenuManager() = default;
            ~CMenuManager() = default;

        public:
            const bool OpenMenu();

            const bool CloseMenu();

            const bool IsMenu() const
            {
                return m_flagOpenMenu;
            }



        private: // constant member



        private: // data member
            CMenuBaseUI* m_menuBaseUI = nullptr;

            bool m_flagOpenMenu = false; // ƒƒjƒ…[‚ğŠJ‚¢‚Ä‚¢‚é‚©
        };
    }
}