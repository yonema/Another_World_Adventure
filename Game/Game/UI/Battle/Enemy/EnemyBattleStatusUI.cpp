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
                        m_basePosition = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }

                    return false;
                });

            // �G��HP�Q�[�W
            m_enemyHPUI = NewGO<CEnemyHPUI>();
            m_enemyHPUI->LoadLevel(m_basePosition);

            // �G�̃u���C�N�Q�[�W
            //m_enemyBreakUI = NewGO<CEnemyBreakUI>();
            //m_enemyBreakUI->LoadLevel(m_basePosition);
        }

        void CEnemyBattleStatusUI::OnDestroy()
        {
            DeleteGO(m_spriteEnemyStatusBase);

            DeleteGO(m_enemyHPUI);
            DeleteGO(m_enemyBreakUI);
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
            // ���ꂾ�ƁA�S���ꂩ���ɂ܂Ƃ܂�̂ŁA
            // �␳�l��ǉ��œ���邱��
            m_spriteEnemyStatusBase->SetPosition(
                { position.x,position.y + m_kUIPositionCorrectionAmountY }
            );

            m_setUIEnemyPosition = { position.x,position.y };

            m_enemyHPUI->SetUIPosition(m_setUIEnemyPosition);
            //m_enemyBreakUI->SetUIPosition(m_setUIEnemyPosition);
        }
    }
}