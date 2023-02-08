#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief �v���C���[��HP�o�[��UI
        */
        class CEnemyBreakUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CEnemyBreakUI() = default;
            ~CEnemyBreakUI() = default;

        public:
            void LoadLevel();

        private:
            void Animation(); // UI�̃A�j���[�V����

        public:
            /**
             * @brief �u���C�N�Q�[�W�̗ʂ��擾
             * @param breakBar �u���C�N�Q�[�W�̗�
            */
            void SetUIEnemyBreakStatus(const float breakBar)
            {
                // �����̔{�����v�Z
                m_barPercentage = breakBar / 100;
            }
            /**
             * @brief UI�̈ʒu���擾
             * @param position �G�̈ʒu
            */
            void SetUIPosition(const CVector2& position);

        private:
            static const char* m_kSpriteBreakBarFilePath;
            static const char* m_kSpriteBreakFilePath;
            static const char* m_kSpriteBreakReductionFilePath;
            static const char* m_kSpriteBaseFilePath;

            static const char* m_kLevel2DFilePath;

        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteBreakBar = nullptr; // �u���C�N�Q�[�W
            CSpriteUI* m_spriteBreak = nullptr; // �u���C�N����Break!
            CSpriteUI* m_spriteBreakReduction = nullptr; // �u���C�N�Q�[�W��������Break!
            CSpriteUI* m_spriteBase = nullptr; // �u���C�N�Q�[�W�̉��n

            // UI�̈ʒu�̕␳�l
            CVector2 m_correctionAmountBreakBar = CVector2::Zero();
            CVector2 m_correctionAmountBreak = CVector2::Zero();
            CVector2 m_correctionAmountBreakReduction = CVector2::Zero();
            CVector2 m_correctionAmountBase = CVector2::Zero();

            float m_barPercentage = 0.0f; // �u���C�N�Q�[�W�̊���

        };
    }
}