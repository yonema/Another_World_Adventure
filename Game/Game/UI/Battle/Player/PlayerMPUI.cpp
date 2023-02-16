#include "YonemaEnginePreCompile.h"
#include "PlayerMPUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CPlayerMPUI::m_kLevel2DFilePath =
            "Assets/Level2D/PlayerStatus.tdl";

        const char* CPlayerMPUI::m_kSpriteMPBarFilePath = 
            "Assets/Images/FitnessBar/Player/Bar_MP.png";
        const char* CPlayerMPUI::m_kSpriteFrameFilePath =
            "Assets/Images/FitnessBar/Common/BarFrame.png";
        const char* CPlayerMPUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Common/BarGroundwork.png";

        const float CPlayerMPUI::m_kMaxBarWidthSize = 0.5f;

        bool CPlayerMPUI::Start()
        {
            return true;
        }

        void CPlayerMPUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ロードするレベル一つ一つにクエリを行う

                // MPバー
                    if ("MP_Bar" == imgData.Name)
                    {
                        // UIクラスを作成
                        m_spriteMPBar = NewGO<CSpriteUI>();
                        m_spriteMPBar->LoadSprite(
                            m_kSpriteMPBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteMPBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // フックしたので、trueを返す
                        return true;
                    }
                    // プレイヤーのMPバーの枠
                    else if ("MP_BarFrame" == imgData.Name)
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
                    // プレイヤーのMPバーの下地
                    else if ("MP_BarGroundwork" == imgData.Name)
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

        void CPlayerMPUI::OnDestroy()
        {
            DeleteGO(m_spriteMPBar);
            DeleteGO(m_spriteFrame);
            DeleteGO(m_spriteBase);
        }

        void CPlayerMPUI::Update(float deltaTime)
        {
            // 毎フレームの処理をここに

            // MPバーのアニメーション
            Animation();

        }

        void CPlayerMPUI::Animation()
        {
            // ゲージの長さ（横幅）を適用
            m_spriteMPBar->SetScale({ m_barWidthSize,m_kMaxBarWidthSize,1.0f });
        }

        void CPlayerMPUI::ActivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteMPBar->SetDrawingFlag(true);
            m_spriteBase->SetDrawingFlag(true);
            m_spriteFrame->SetDrawingFlag(true);

            m_spriteMPBar->Activate();
            m_spriteBase->Activate();
            m_spriteFrame->Activate();
        }

        void CPlayerMPUI::DeactivatePlayerBattleStatusDrawingFlag()
        {
            if (nullptr == this) {
                return;
            }

            m_spriteMPBar->SetDrawingFlag(false);
            m_spriteBase->SetDrawingFlag(false);
            m_spriteFrame->SetDrawingFlag(false);

            m_spriteMPBar->Deactivate();
            m_spriteBase->Deactivate();
            m_spriteFrame->Deactivate();
        }
    }
}