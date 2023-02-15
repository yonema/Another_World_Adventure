#include "YonemaEnginePreCompile.h"
#include "EnemyBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "EnemyHPUI.h"
#include "EnemyBreakUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBattleStatusUI::m_kLevel2DFilePath =
            "Assets/Level2D/EnemyStatusBase.tdl";

        const char* CEnemyBattleStatusUI::m_kSpriteEnemyStatusBaseFilePath = 
            "Assets/Images/FitnessBar/Enemy/EnemyStatusBase.png";

        const float CEnemyBattleStatusUI::m_kUIPositionCorrectionAmountY = 13.0f;

        const float CEnemyBattleStatusUI::m_kDrawingAngle = 90.0f;


        bool CEnemyBattleStatusUI::Start()
        {
            return true;
        }

        void CEnemyBattleStatusUI::LoadLevel()
        {
            // �v���C���[�̃o�g���X�e�[�^�X�̓y��
            m_level.Load(m_kLevel2DFilePath, [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �G�X�e�[�^�X�̓y�䕔��
                    if ("EnemyStatusBase" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteEnemyStatusBase = NewGO<CSpriteUI>();
                        m_spriteEnemyStatusBase->LoadSprite(
                            m_kSpriteEnemyStatusBaseFilePath,
                            imgData.SpriteSize,
                            static_cast<EnRendererPriority>(imgData.Priority),
                            EnAlphaBlendMode::enTrans
                        );
                        m_spriteEnemyStatusBase->LoadInitData(
                            imgData.Position,
                            imgData.Scale,
                            imgData.Pivot
                        );

                        // �y�䕔���ȊO��UI�̈ʒu�̊�ɂȂ�ʒu���擾
                        m_initialPosition = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });

            // �G��HP�Q�[�W
            m_enemyHPUI = NewGO<CEnemyHPUI>();
            m_enemyHPUI->LoadLevel();

            // �G�̃u���C�N�Q�[�W
            //m_enemyBreakUI = NewGO<CEnemyBreakUI>();
            //m_enemyBreakUI->LoadLevel();
        }

        void CEnemyBattleStatusUI::OnDestroy()
        {
            DeleteGO(m_spriteEnemyStatusBase);

            DeleteGO(m_enemyHPUI);
            //DeleteGO(m_enemyBreakUI);
        }

        void CEnemyBattleStatusUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������



        }

        void CEnemyBattleStatusUI::SetUIEnemyStatus(const float hp, const float maxHP, const float breakBar)
        {
            m_enemyHPUI->SetUIEnemyHPStatus(hp, maxHP);
            //m_enemyBreakUI->SetUIEnemyBreakStatus(breakBar);
        }

        void CEnemyBattleStatusUI::SetUIEnemyPosition(const CVector3& position)
        {
            if (true == CheckDrawUI(position)) {
                m_spriteEnemyStatusBase->SetDrawingFlag(true);
            }
            else {
                m_spriteEnemyStatusBase->SetDrawingFlag(false);

                return;
            }

            CVector3 targetPosition = { position.x,position.y + m_kUIPositionCorrectionAmountY,position.z };
            CVector2 uiPosition = MainCamera()->CalcScreenPositionFromWorldPosition(targetPosition);



            // ���ꂾ�ƁA�S���ꂩ���ɂ܂Ƃ܂�̂ŁA
            // �␳�l��ǉ��œ���邱��
            m_spriteEnemyStatusBase->SetPosition(
                {
                    uiPosition.x + m_initialPosition.x,
                    uiPosition.y + m_initialPosition.y
                }
            );

            m_setUIEnemyPosition = { uiPosition.x,uiPosition.y };

            m_enemyHPUI->SetUIPosition(m_setUIEnemyPosition);
            //m_enemyBreakUI->SetUIPosition(m_setUIEnemyPosition);
        }

        const bool CEnemyBattleStatusUI::CheckDrawUI(const CVector3& targetPosition)
        {
            CVector3 normalizeCameraForwardDirection = MainCamera()->GetForwardDirection();
            CVector3 normalizeTargetPosition = targetPosition - MainCamera()->GetPosition();

            normalizeCameraForwardDirection.Normalize();
            normalizeTargetPosition.Normalize();

            float resultFieldOfView = 
                nsMath::RadToDeg(std::acos(nsMath::Dot(normalizeCameraForwardDirection, normalizeTargetPosition)));

            // ����ɓ����Ă��邩�v�Z
            if (resultFieldOfView <= m_kDrawingAngle) {
                // �������̂Ő���
                return true;
            }

            // ���s
            return false;
        }
    }
}