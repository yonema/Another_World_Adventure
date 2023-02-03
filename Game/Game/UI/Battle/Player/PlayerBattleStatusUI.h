#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;
        class CPlayerHPUI;
        class CPlayerMPUI;
        class CPlayerSPUI;

        class CPlayerBattleStatusUI : public IGameObject
        {
        public:
            bool Start() override final;

            void OnDestroy() override final;

            void Update(float deltaTime) override final;

        public:
            CPlayerBattleStatusUI() = default;
            ~CPlayerBattleStatusUI() = default;

        public:
            void LoadLevel();


        public: // Set function
            /**
             * @brief UI�ɕK�v�ȃv���C���[�̃X�e�[�^�X�����擾
             * @param hp �̗�
             * @param maxHP �̗͂̍ő�l
             * @param mp MP
             * @param maxMP MP�̍ő�l
             * @param sp �X�^�~�i
             * @param maxSP �X�^�~�i�̍ő�l
            */
            void SetUIPlayerStatus(
                const float hp, const float maxHP,
                const float mp, const float maxMP,
                const float sp, const float maxSP
            );

        private:
            static const char* m_kSpritePlayerStatusBaseFilePath;
            static const char* m_kLevel2DFilePath;


        private: // data member
            // �������ꂽ��A���̂��ǉ�
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spritePlayerStatusBase = nullptr;

            CPlayerHPUI* m_playerHPUI = nullptr;
            CPlayerMPUI* m_playerMPUI = nullptr;
            CPlayerSPUI* m_playerSPUI = nullptr;
        };
    }
}