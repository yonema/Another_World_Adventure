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
            void LoadLevel(const char* tdlFilePath, const CVector2& basePosition);

        private:
            void Animation(); // UI�̃A�j���[�V����

        public:
            /**
             * @brief UI�ɕK�v�ȓG�̗̑͂̏����擾
             * @param hp �̗�
             * @param maxHP �̗͂̍ő�l
            */
            void SetUIEnemyHPStatus(const float hp, const float maxHP)
            {
                // �����̔{�����v�Z
                m_barWidthSize = hp / maxHP;
            }
            /**
             * @brief UI�̈ʒu���擾
             * @param position �G�̈ʒu
            */
            void SetUIPosition(const CVector2& position)
            {
                m_spriteHPBar->SetPosition(position + m_correctionAmountHPBar);
                m_spriteFrame->SetPosition(position + m_correctionAmountFrame);
                m_spriteBase->SetPosition(position + m_correctionAmountBase);
                m_spriteDanger->SetPosition(position + m_correctionAmountDanger);
            }

        private:
            static const char* m_kSpriteHPBarFilePath;
            static const char* m_kSpriteFrameFilePath;
            static const char* m_kSpriteBaseFilePath;
            static const char* m_kSpriteDangerFilePath;



        private: // data member
            // �������ꂽ��A���̂��ǉ�
            // C2DLevel m_level;

            CSpriteUI* m_spriteHPBar = nullptr; // HP�o�[
            CSpriteUI* m_spriteFrame = nullptr; // �o�[�̘g
            CSpriteUI* m_spriteBase = nullptr; // HP�o�[�̉��n
            CSpriteUI* m_spriteDanger = nullptr; // �s���`����HP�o�[

            // UI�̈ʒu�̕␳�l
            CVector2 m_correctionAmountHPBar = CVector2::Zero();
            CVector2 m_correctionAmountFrame = CVector2::Zero();
            CVector2 m_correctionAmountBase = CVector2::Zero();
            CVector2 m_correctionAmountDanger = CVector2::Zero();

            float m_barWidthSize = 1.0f; // �v���C���[�̗̑̓o�[�̉����̔{��

        };
    }
}