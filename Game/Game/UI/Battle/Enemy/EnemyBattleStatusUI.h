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
            /**
             * @brief UIを描画するか確認
             * @param targetPosition 描画するUIを保持する敵
             * @return 描画するか
            */
            const bool CheckDrawUI(const CVector3& targetPosition);

            void CheckEnemyDistance(const CVector3& targetPosition);


        private: // constant data member
            static const char* m_kLevel2DFilePath; // レベルファイルのパス
            static const char* m_kSpriteEnemyStatusBaseFilePath; // 画像のパス

            // UIの取得した敵の位置に対しての補正値（Y座標）
            static const float m_kUIPositionCorrectionAmountY;
            static const float m_kUIPositionCorrectionAmountX;
            static const float m_kDrawingAngle; // UI表示の判定角度

            static const float m_kEnemyMaximumDistance;

        private: // data member
            ////////////////////////////////////////////////////////////
            // レベル、画像
            ////////////////////////////////////////////////////////////

            nsLevel2D::CLevel2D m_level; // レベルファイルクラス

            CSpriteUI* m_spriteEnemyStatusBase = nullptr; // 敵のステータス

            ////////////////////////////////////////////////////////////
            // UIクラス
            ////////////////////////////////////////////////////////////

            CEnemyHPUI* m_enemyHPUI = nullptr; // 敵の体力ゲージUIクラス
            CEnemyBreakUI* m_enemyBreakUI = nullptr; // 敵のブレイクゲージUIクラス

            ////////////////////////////////////////////////////////////
            // ステータス
            ////////////////////////////////////////////////////////////

            CVector2 m_initialPosition = CVector2::Zero(); // UIの初期位置
            CVector2 m_initialScale = CVector2::One();

            CVector2 m_setUIEnemyPosition = CVector2::Zero();

        };
    }
}