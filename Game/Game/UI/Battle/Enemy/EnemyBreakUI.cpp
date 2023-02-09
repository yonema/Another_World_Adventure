#include "YonemaEnginePreCompile.h"
#include "EnemyBreakUI.h"

#include "../../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBreakUI::m_kLevel2DFilePath =
            "Assets/Level2D/BreakGauge.tdl";
        
        const char* CEnemyBreakUI::m_kSpriteBreakBarFilePath =
            "Assets/Images/FitnessBar/Enemy/Gauge_Break.png";
        const char* CEnemyBreakUI::m_kSpriteBreakFilePath =
            "Assets/Images/FitnessBar/Enemy/Break_GaugeMax.png";
        const char* CEnemyBreakUI::m_kSpriteBreakReductionFilePath =
            "Assets/Images/FitnessBar/Enemy/Break_GaugeDecrease.png";
        const char* CEnemyBreakUI::m_kSpriteBaseFilePath =
            "Assets/Images/FitnessBar/Enemy/Gauge_Break_Groundwork.png";

        const float CEnemyBreakUI::m_kMaxBarHeightSize = 0.3f;

        bool CEnemyBreakUI::Start()
        {
            return true;
        }

        void CEnemyBreakUI::LoadLevel()
        {
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                // �u���C�N�Q�[�W
                    if ("Gauge_Break" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBreakBar = NewGO<CSpriteUI>();
                        m_spriteBreakBar->LoadSprite(
                            m_kSpriteBreakBarFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBreakBar->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // UI�̏����ʒu���擾
                        m_initialPositionBreakBar = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �u���C�N�Q�[�W��MAX�ɂȂ����Ƃ��ɕ\������UI
                    else if ("Break_GaugeMax" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBreak = NewGO<CSpriteUI>();
                        m_spriteBreak->LoadSprite(
                            m_kSpriteBreakFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBreak->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );


                        m_spriteBreak->SetDrawingFlag(false);

                        // UI�̏����ʒu���擾
                        m_initialPositionBreak = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �u���C�N�Q�[�W���������ɕ\������UI
                    else if ("Break_GaugeDecrease" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBreakReduction = NewGO<CSpriteUI>();
                        m_spriteBreakReduction->LoadSprite(
                            m_kSpriteBreakReductionFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteBreakReduction->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        m_spriteBreakReduction->SetDrawingFlag(false);

                        // UI�̏����ʒu���擾
                        m_initialPositionBreakReduction = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �u���C�N�Q�[�W�̉��n
                    else if ("Gauge_Break_Groundwork" == imgData.Name)
                    {
                        // UI�N���X���쐬
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

                        // UI�̏����ʒu���擾
                        m_initialPositionBase = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });
        }

        void CEnemyBreakUI::OnDestroy()
        {
            DeleteGO(m_spriteBreakBar);
            DeleteGO(m_spriteBreak);
            DeleteGO(m_spriteBreakReduction);
            DeleteGO(m_spriteBase);
        }

        void CEnemyBreakUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

            // HP�o�[�̃A�j���[�V����
            Animation();

        }

        void CEnemyBreakUI::Animation()
        {
            // �Q�[�W�̒����i�����j��K�p
            m_spriteBreakBar->SetScale({ 1.0f,m_barPercentage,1.0f });
        }

        void CEnemyBreakUI::SetUIPosition(const CVector2& position)
        {
            m_spriteBreakBar->SetPosition(position + m_initialPositionBreakBar);
            m_spriteBreak->SetPosition(position + m_initialPositionBreak);
            m_spriteBreakReduction->SetPosition(position + m_initialPositionBreakReduction);
            m_spriteBase->SetPosition(position + m_initialPositionBase);
        }
    }
}