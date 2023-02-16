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
            /**
             * @brief UI��`�悷�邩�m�F
             * @param targetPosition �`�悷��UI��ێ�����G
             * @return �`�悷�邩
            */
            const bool CheckDrawUI(const CVector3& targetPosition);

            void CheckEnemyDistance(const CVector3& targetPosition);


        private: // constant data member
            static const char* m_kLevel2DFilePath; // ���x���t�@�C���̃p�X
            static const char* m_kSpriteEnemyStatusBaseFilePath; // �摜�̃p�X

            // UI�̎擾�����G�̈ʒu�ɑ΂��Ă̕␳�l�iY���W�j
            static const float m_kUIPositionCorrectionAmountY;
            static const float m_kUIPositionCorrectionAmountX;
            static const float m_kDrawingAngle; // UI�\���̔���p�x

            static const float m_kEnemyMaximumDistance;

        private: // data member
            ////////////////////////////////////////////////////////////
            // ���x���A�摜
            ////////////////////////////////////////////////////////////

            nsLevel2D::CLevel2D m_level; // ���x���t�@�C���N���X

            CSpriteUI* m_spriteEnemyStatusBase = nullptr; // �G�̃X�e�[�^�X

            ////////////////////////////////////////////////////////////
            // UI�N���X
            ////////////////////////////////////////////////////////////

            CEnemyHPUI* m_enemyHPUI = nullptr; // �G�̗̑̓Q�[�WUI�N���X
            CEnemyBreakUI* m_enemyBreakUI = nullptr; // �G�̃u���C�N�Q�[�WUI�N���X

            ////////////////////////////////////////////////////////////
            // �X�e�[�^�X
            ////////////////////////////////////////////////////////////

            CVector2 m_initialPosition = CVector2::Zero(); // UI�̏����ʒu
            CVector2 m_initialScale = CVector2::One();

            CVector2 m_setUIEnemyPosition = CVector2::Zero();

        };
    }
}