#include "YonemaEnginePreCompile.h"
#include "PlayerBattleStatusUI.h"

#include "../../SpriteUI.h"
#include "PlayerHPUI.h"
#include "PlayerMPUI.h"
#include "PlayerSPUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        const char* m_kSpritePlayerStatusBaseFilePath =
            "Assets/Image/FitnessBar/Player/PlayerStatusBase.png";

        bool CPlayerBattleStatusUI::Start()
        {
            return true;
        }

        void CPlayerBattleStatusUI::LoadLevel(const char* tdlFilePath)
        {
            // �v���C���[�̃o�g���X�e�[�^�X�̓y��
            m_level.Init(tklFilePath, [&](LevelObjectData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��

                    // �v���C���[�X�e�[�^�X�̓y�䕔��
                    if (imgData.EqualObjectName(L"�v���C���[�X�e�[�^�X�̓y�䕔��") == true)
                    {
                        // UI�N���X���쐬
                        m_spritePlayerStatusBase = NewGO<CSpriteUI>();
                        m_spritePlayerStatusBase->LoadSprite(m_kSpritePlayerStatusBaseFilePath);
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spritePlayerStatusBase->SetPosition(imgData.position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spritePlayerStatusBase->SetPivot(imgData.pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });

            // �v���C���[��HP�Q�[�W
            m_playerHPUI = NewGO<CPlayerHPUI>();
            m_playerHPUI->LoadLevel(tdlFilePath);

            // �v���C���[��MP�Q�[�W
            m_playerMPUI = NewGO<CPlayerMPUI>();
            m_playerMPUI->LoadLevel(tdlFilePath);

            // �v���C���[��SP�Q�[�W
            m_playerSPUI = NewGO<CPlayerSPUI>();
            m_playerSPUI->LoadLevel(tdlFilePath);
        }

        void CPlayerBattleStatusUI::OnDestroy()
        {
            DeleteGO(m_spritePlayerStatusBase);

            DeleteGO(m_playerHPUI);
            DeleteGO(m_playerMPUI);
            DeleteGO(m_playerSPUI);
        }

        void CPlayerBattleStatusUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������



        }
    }
}