#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CPlayerHPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerHPUI() = default;
            ~CPlayerHPUI() = default;

        public:
            void LoadLevel();

        private:
            void Animation(); // UI�̃A�j���[�V����

            void ChangeDangerUI(const bool flagDanger);

            const bool StartDecreaseBarAnimationTimer();

            /**
             * @brief �x��Č�������Q�[�W�̃A�j���[�V����
            */
            void DecreaseBarAnimation();

        public:
            /**
             * @brief UI�ɕK�v�ȃv���C���[�̗̑͂̏����擾
             * @param hp �̗�
             * @param maxHP �̗͂̍ő�l
            */
            void SetUIPlayerHPStatus(const float hp, const float maxHP)
            {
                // �����̔{�����v�Z
                m_barWidthSize = hp / maxHP * m_kMaxBarWidthSize;

                if (m_oldDecreaseBarWidthSize != m_barWidthSize) {
                    m_startDecreaseBarAnimationTimer = 0;
                }
            }

        private:
            // �t�@�C���p�X
            static const char* m_kSpriteHPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;
            static const char* m_kSpriteDangerFilePath;
            static const char* m_kSpriteDecreaaseFilePath;

            // �s���`���胉�C��
            static const float m_kDangerLine;
            static const float m_kStartDecreaseBarAnimationTime;
            static const float m_kStartDecreaseBarAnimationTimeAmount;
            // �����A�j���[�V�����̌�����
            static const float m_kDecreaseBarDecreaseAmount;

            static const char* m_kLevel2DFilePath;

            static const float m_kMaxBarWidthSize;


        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteHPBar = nullptr; // HP�o�[
            CSpriteUI* m_spriteFrame = nullptr; // �o�[�̘g
            CSpriteUI* m_spriteBase = nullptr; // HP�o�[�̉��n
            CSpriteUI* m_spriteDanger = nullptr; // �s���`����HP�o�[
            CSpriteUI* m_spriteDecrease = nullptr; // HP�o�[�̃f�B���C�A�j���[�V�����o�[

            float m_barWidthSize = m_kMaxBarWidthSize; // �v���C���[�̗̑̓o�[�̉����̔{��
            float m_decreaseBarWidthSize = m_kMaxBarWidthSize; // ���Ƃ���ǂ��Č���Q�[�W�̉����̔{��
            float m_startDecreaseBarAnimationTimer = 0.0f; // ���Ƃ���ǂ��ăQ�[�W������A�j���[�V�����̃^�C�}�[

            float m_oldDecreaseBarWidthSize = m_kMaxBarWidthSize; // �Q�[�W����������O�̉����̔{��
        };
    }
}