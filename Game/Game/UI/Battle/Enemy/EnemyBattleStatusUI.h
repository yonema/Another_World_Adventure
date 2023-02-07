#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;
        class CEnemyHPUI;
        class CEnemyBreakUI;

        class CEnemyBattleStatusUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CEnemyBattleStatusUI() = default;
            ~CEnemyBattleStatusUI() = default;

        public:
            void LoadLevel();


        public: // Set function
            /**
             * @brief UI�ɕK�v�ȃX�e�[�^�X�����擾
             * @param hp �̗�
             * @param maxHP �̗͂̍ő�l
             * @param breakBar �u���C�N�Q�[�W�̌��ݗ�
            */
            void SetUIEnemyStatus(const float hp, const float maxHP, const float breakBar);
            /**
             * @brief UI�̈ʒu���擾
             * @param position �G�̈ʒu
            */
            void SetUIEnemyPosition(const CVector3& position);

            const bool CheckDrawUI(const CVector3& targetPosition);


        private: // constant data member
            // UI�̎擾�����G�̈ʒu�ɑ΂��Ă̕␳�l�iY���W�j
            static constexpr float m_kUIPositionCorrectionAmountY = -100.0f;
            static const char* m_kSpriteEnemyStatusBaseFilePath;

            static const char* m_kLevel2DFilePath;

        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteEnemyStatusBase = nullptr; // �G�̃X�e�[�^�X

            CEnemyHPUI* m_enemyHPUI = nullptr; // �G�̗̑̓Q�[�W
            CEnemyBreakUI* m_enemyBreakUI = nullptr; // �G�̃u���C�N�Q�[�W

            CVector2 m_basePosition = CVector2::Zero(); // UI�̊�ƂȂ�ʒu

            CVector2 m_initialPosition = CVector2::Zero(); // UI�̏����ʒu

            CVector2 m_setUIEnemyPosition = CVector2::Zero();

        };
    }
}