#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CPlayerMPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerMPUI() = default;
            ~CPlayerMPUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UI�̃A�j���[�V����

        public:
            /**
             * @brief �v���C���[��MP���擾
             * @param mp MP
             * @param maxMP MP�̍ő�l
            */
            void SetUIPlayerMPStatus(const float mp, const float maxMP)
            {
                // �����̔{�����v�Z
                m_barWidthSize = mp / maxMP;
            }

        private:
            static const char* m_kSpriteMPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;

        private: // data member
            // �������ꂽ��A���̂��ǉ�
            // C2DLevel m_level;

            CSpriteUI* m_spriteMPBar = nullptr; // HP�o�[
            CSpriteUI* m_spriteFrame = nullptr; // �o�[�̘g
            CSpriteUI* m_spriteBase = nullptr; // HP�o�[�̉��n

            float m_barWidthSize = 1.0f; // �v���C���[�̗̑̓o�[�̉����̔{��

        };
    }
}