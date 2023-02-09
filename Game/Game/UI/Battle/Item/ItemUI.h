#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CItemUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CItemUI() = default;
            ~CItemUI() = default;

        public:
            void LoadLevel();

        private:
            void Animation(); // UI�̃A�j���[�V����


        public:
            void ActiveDrawing();

            void DeactiveDrawing();



        private: // constant member
            static const char* m_kLevel2DFilePath;

            static const char* m_kItemBaseSpriteFilePath;



        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteBase = nullptr;
            //CSpriteUI* m_spriteItemIcon = nullptr;

        };
    }
}