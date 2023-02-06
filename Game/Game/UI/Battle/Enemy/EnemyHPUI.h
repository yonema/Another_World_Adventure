#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CEnemyHPUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CEnemyHPUI() = default;
            ~CEnemyHPUI() = default;

        public:
            void LoadLevel(const CVector2& basePosition);

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
             * @brief UI�ɕK�v�ȓG�̗̑͂̏����擾
             * @param hp �̗�
             * @param maxHP �̗͂̍ő�l
            */
            void SetUIEnemyHPStatus(const float hp, const float maxHP)
            {
                // �����̔{�����v�Z
                m_barWidthSize = hp / maxHP * m_kMaxBarWidthSize;

                if (m_oldDecreaseBarWidthSize != m_barWidthSize) {
                    m_startDecreaseBarAnimationTimer = 0;
                }
            }
            /**
             * @brief UI�̈ʒu���擾
             * @param position �G�̈ʒu
            */
            void SetUIPosition(const CVector2& position);

        private:
            static const char* m_kSpriteHPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;
            static const char* m_kSpriteDangerFilePath;
            static const char* m_kSpriteDecreaaseFilePath;

            static const char* m_kLevel2DFilePath;

            static const float m_kMaxBarWidthSize;

            static const float m_kDangerLine;


            static const float m_kStartDecreaseBarAnimationTime;
            static const float m_kStartDecreaseBarAnimationTimeAmount;
            // �����A�j���[�V�����̌�����
            static const float m_kDecreaseBarDecreaseAmount;



        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteHPBar = nullptr; // HP�o�[
            CSpriteUI* m_spriteFrame = nullptr; // �o�[�̘g
            CSpriteUI* m_spriteBase = nullptr; // HP�o�[�̉��n
            CSpriteUI* m_spriteDanger = nullptr; // �s���`����HP�o�[
            CSpriteUI* m_spriteDecrease = nullptr; // HP�o�[�̃f�B���C�A�j���[�V�����o�[

            // UI�̈ʒu�̕␳�l
            CVector2 m_initialPositionHPBar = CVector2::Zero();
            CVector2 m_initialPositionFrame = CVector2::Zero();
            CVector2 m_initialPositionBase = CVector2::Zero();
            CVector2 m_initialPositionDanger = CVector2::Zero();
            CVector2 m_initialPositionDecrease = CVector2::Zero();

            float m_barWidthSize = m_kMaxBarWidthSize; // �v���C���[�̗̑̓o�[�̉����̔{��

            float m_decreaseBarWidthSize = m_kMaxBarWidthSize; // ���Ƃ���ǂ��Č���Q�[�W�̉����̔{��
            float m_startDecreaseBarAnimationTimer = 0.0f; // ���Ƃ���ǂ��ăQ�[�W������A�j���[�V�����̃^�C�}�[

            float m_oldDecreaseBarWidthSize = m_kMaxBarWidthSize; // �Q�[�W����������O�̉����̔{��


        };
    }
}