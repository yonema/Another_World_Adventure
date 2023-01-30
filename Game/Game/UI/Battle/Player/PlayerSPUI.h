#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CPlayerSPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerSPUI() = default;
            ~CPlayerSPUI() = default;

        public:
            void LoadLevel(const char* tdlFilePath);

        private:
            void Animation(); // UI�̃A�j���[�V����

        public:
            /**
             * @brief �v���C���[��SP���擾
             * @param sp SP
             * @param maxSP SP�̍ő�l
            */
            void SetUIPlayerSPStatus(const float sp, const float maxSP)
            {
                // �����̔{�����v�Z
                m_barWidthSize = sp / maxSP;
            }

        private:
            static const char* m_kSpriteSPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;

        private: // data member
            // �������ꂽ��A���̂��ǉ�
            // C2DLevel m_level;

            CSpriteUI* m_spriteSPBar = nullptr; // HP�o�[
            CSpriteUI* m_spriteFrame = nullptr; // �o�[�̘g
            CSpriteUI* m_spriteBase = nullptr; // HP�o�[�̉��n

            float m_barWidthSize = 1.0f; // �v���C���[�̗̑̓o�[�̉����̔{��
        };
    }
}