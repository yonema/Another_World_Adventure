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
            "Assets/Image/FitnessBar/Enemy/EnemyStatusBase.png";

        bool CEnemyBattleStatusUI::Start()
        {
            return true;
        }

        void CEnemyBattleStatusUI::LoadLevel(const char* tdlFilePath)
        {
            // �v���C���[�̃o�g���X�e�[�^�X�̓y��
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �G�X�e�[�^�X�̓y�䕔��
                    if (imgData.EqualObjectName(L"�v���C���[�X�e�[�^�X�̓y�䕔��") == true)
                    {
                        // UI�N���X���쐬
                        m_spriteEnemyStatusBase = NewGO<CSpriteUI>();
                        m_spriteEnemyStatusBase->LoadSprite(m_kSpriteEnemyStatusBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteEnemyStatusBase->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteEnemyStatusBase->SetPivot(imgData.pivot);

                        // �y�䕔���ȊO��UI�̈ʒu�̊�ɂȂ�ʒu���擾
                        m_basePosition = imgData.position;

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
    }
}