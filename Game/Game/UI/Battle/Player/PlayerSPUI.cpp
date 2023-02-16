#include "YonemaEnginePreCompile.h"
#include "PlayerSPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerSPUI::m_kLevel2DFilePath =
            "Assets/Level2D/PlayerStatus.tdl";

        const char* CPlayerSPUI::m_kSpriteSPBarFilePath =
            "Assets/Images/FitnessBar/Player/Bar_SP.png";
        const char* CPlayerSPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CPlayerSPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";

        const float CPlayerSPUI::m_kMaxBarWidthSize = 0.5f;

        bool CPlayerSPUI::Start()
        {
            return true;
        }

        void CPlayerSPUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // SPバー
                    if ("SP_Bar" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteSPBar = NewGO<CSpriteUI>();
                        m_spriteSPBar->LoadSprite(
                            m_kSpriteSPBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteSPBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのSPバーの枠
                    else if ("SP_BarFrame" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteFrame = NewGO<CSpriteUI>();
                        m_spriteFrame->LoadSprite(
                            m_kSpriteFrameFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteFrame->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのSPバーの下地
                    else if ("SP_BarGroundwork" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite(
                            m_kSpriteBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // フックしたので、trueを返す
                        return true;
                    }

                    return true;
                    return false;
                });
        }

        void CPlayerSPUI::OnDestroy()
        {
            DeleteGO(m_spriteSPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
        }

        void CPlayerSPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // SPバーのアニメーション
            Animation();

        }

        void CPlayerSPUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            m_spriteSPBar->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
        }

        void CPlayerSPUI::ActivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteSPBar->SetDrawingFlag(true);
            m_spriteBase->SetDrawingFlag(true);
            m_spriteFrame->SetDrawingFlag(true);

            m_spriteSPBar->Activate();
            m_spriteBase->Activate();
            m_spriteFrame->Activate();
        }

        void CPlayerSPUI::DeactivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteSPBar->SetDrawingFlag(false);
            m_spriteBase->SetDrawingFlag(false);
            m_spriteFrame->SetDrawingFlag(false);

            m_spriteSPBar->Deactivate();
            m_spriteBase->Deactivate();
            m_spriteFrame->Deactivate();
        }
    }
}