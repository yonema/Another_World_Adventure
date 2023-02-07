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
             * @brief UIに必要なステータス情報を取得
             * @param hp 体力
             * @param maxHP 体力の最大値
             * @param breakBar ブレイクゲージの現在量
            */
            void SetUIEnemyStatus(const float hp, const float maxHP, const float breakBar);
            /**
             * @brief UIの位置を取得
             * @param position 敵の位置
            */
            void SetUIEnemyPosition(const CVector3& position);

            const bool CheckDrawUI(const CVector3& targetPosition);


        private: // constant data member
            // UIの取得した敵の位置に対しての補正値（Y座標）
            static constexpr float m_kUIPositionCorrectionAmountY = -100.0f;
            static const char* m_kSpriteEnemyStatusBaseFilePath;

            static const char* m_kLevel2DFilePath;

        private: // data member
            // 実装されたら、下のやつを追加
            nsLevel2D::CLevel2D m_level;

            CSpriteUI* m_spriteEnemyStatusBase = nullptr; // 敵のステータス

            CEnemyHPUI* m_enemyHPUI = nullptr; // 敵の体力ゲージ
            CEnemyBreakUI* m_enemyBreakUI = nullptr; // 敵のブレイクゲージ

            CVector2 m_basePosition = CVector2::Zero(); // UIの基準となる位置

            CVector2 m_initialPosition = CVector2::Zero(); // UIの初期位置

            CVector2 m_setUIEnemyPosition = CVector2::Zero();

        };
    }
}