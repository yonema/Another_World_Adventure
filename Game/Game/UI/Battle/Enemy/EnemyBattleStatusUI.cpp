#include "YonemaEnginePreCompile.h"
#include "EnemyBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "EnemyHPUI.h"
#include "EnemyBreakUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* CEnemyBattleStatusUI::m_kSpriteEnemyStatusBaseFilePath = 
            "Assets/Images/FitnessBar/Enemy/EnemyStatusBase.png";

        bool CEnemyBattleStatusUI::Start()
        {
            return true;
        }

        void CEnemyBattleStatusUI::LoadLevel(const char* tdlFilePath)
        {
            // �v���C���[�̃o�g���X�e�[�^�X�̓y��
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �G�X�e�[�^�X�̓y�䕔��
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteEnemyStatusBase = NewGO<CSpriteUI>();
                        m_spriteEnemyStatusBase->LoadSprite(m_kSpriteEnemyStatusBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteEnemyStatusBase->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteEnemyStatusBase->SetPivot(imgData.Pivot);

                        // �y�䕔���ȊO��UI�̈ʒu�̊�ɂȂ�ʒu���擾
                        m_basePosition = imgData.Position;

                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });

            // �G��HP�Q�[�W
            m_enemyHPUI = NewGO<CEnemyHPUI>();
            m_enemyHPUI->LoadLevel(tdlFilePath, m_basePosition);

            // �G�̃u���C�N�Q�[�W
            m_enemyBreakUI = NewGO<CEnemyBreakUI>();
            m_enemyBreakUI->LoadLevel(tdlFilePath, m_basePosition);
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
            m_enemyBreakUI->SetUIEnemyBreakStatus(breakBar);
        }

        void CEnemyBattleStatusUI::SetUIEnemyPosition(const CVector2& position)
        {
            // ���ꂾ�ƁA�S���ꂩ���ɂ܂Ƃ܂�̂ŁA
            // �␳�l��ǉ��œ���邱��
            m_spriteEnemyStatusBase->SetPosition(
                { position.x,position.y + m_kUIPositionCorrectionAmountY }
            );

            m_enemyHPUI->SetUIPosition(position);
            m_enemyBreakUI->SetUIPosition(position);
        }
    }
}