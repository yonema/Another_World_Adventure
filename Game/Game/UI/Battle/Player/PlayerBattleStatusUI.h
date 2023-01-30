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
            void LoadLevel(const char* tdlFilePath);


        public: // Set function
            /**
             * @brief UIに必要なプレイヤーのステータス情報を取得
             * @param hp 体力
             * @param maxHP 体力の最大値
             * @param mp MP
             * @param maxMP MPの最大値
             * @param sp スタミナ
             * @param maxSP スタミナの最大値
            */
            void SetUIPlayerStatus(
                const float hp, const float maxHP,
                const float mp, const float maxMP,
                const float sp, const float maxSP
            )
            {
                m_playerHPUI->SetUIPlayerHPStatus(hp, maxHP);
                m_playerMPUI->SetUIPlayerMPStatus(mp, maxMP);
                m_playerSPUI->SetUIPlayerSPStatus(sp, maxSP);
            }

        private:
            static const char* m_kSpritePlayerStatusBaseFilePath;


        private: // data member
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spritePlayerStatusBase = nullptr;

            CPlayerHPUI* m_playerHPUI = nullptr;
            CPlayerMPUI* m_playerMPUI = nullptr;
            CPlayerSPUI* m_playerSPUI = nullptr;
        };
    }
}