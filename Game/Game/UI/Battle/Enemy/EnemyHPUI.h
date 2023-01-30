#pragma once

namespace nsAWA
{
    namespace nsUI
    {
        class CSpriteUI;

        /**
         * @brief プレイヤーのHPバーのUI
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
            void Animation(); // UIのアニメーション

        public:
            /**
             * @brief UIに必要な敵の体力の情報を取得
             * @param hp 体力
             * @param maxHP 体力の最大値
            */
            void SetUIEnemyHPStatus(const float hp, const float maxHP)
            {
                // 横幅の倍率を計算
                m_barWidthSize = hp / maxHP;
            }
            /**
             * @brief UIの位置を取得
             * @param position 敵の位置
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
            // 実装されたら、下のやつを追加
            // C2DLevel m_level;

            CSpriteUI* m_spriteHPBar = nullptr; // HPバー
            CSpriteUI* m_spriteFrame = nullptr; // バーの枠
            CSpriteUI* m_spriteBase = nullptr; // HPバーの下地
            CSpriteUI* m_spriteDanger = nullptr; // ピンチ時のHPバー

            // UIの位置の補正値
            CVector2 m_correctionAmountHPBar = CVector2::Zero();
            CVector2 m_correctionAmountFrame = CVector2::Zero();
            CVector2 m_correctionAmountBase = CVector2::Zero();
            CVector2 m_correctionAmountDanger = CVector2::Zero();

            float m_barWidthSize = 1.0f; // プレイヤーの体力バーの横幅の倍率

        };
    }
}