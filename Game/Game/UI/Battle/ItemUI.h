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
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UI�̃A�j���[�V����

        public:
            /**
             * @brief �v���C���[��HP��
             * @param hp �̗�
             * @param maxHP �̗͂̍ő�l
            */
            void SetUIPlayerMPStatus(const float& mp, const float& maxMP)
            {
                // �����̔{�����v�Z
                m_barWidthSize = mp / maxMP;
            }

        private: // data member
            // �������ꂽ��A���̂��ǉ�
            // C2DLevel m_level;

            CSpriteUI* m_spriteBase = nullptr; // HP�o�[


            float m_barWidthSize = 1.0f; // �v���C���[�̗̑̓o�[�̉����̔{��

        };
    }
}