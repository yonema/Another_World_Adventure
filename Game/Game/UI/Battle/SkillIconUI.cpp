#include "YonemaEnginePreCompile.h"
#include "SkillIconUI.h"

#include "../SpriteUI.h"

namespace nsAWA
{
    namespace nsUI
    {
        bool CSkillIconUI::Start()
        {
            return true;
        }

        void CSkillIconUI::LoadLevel(const char* tdlFilePath)
        {
            m_level.Load("", [&](const nsLevel2D::SLevel2DSpriteData& imgData)
                { // ���[�h���郌�x�����ɃN�G�����s��
                //�X�L���A�C�R���̓y��
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteBase = NewGO<CSpriteUI>();
                        m_spriteBase->LoadSprite("�t�@�C���p�X");
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteBase->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                    // �X�L���A�C�R���̃C���X�g
                    if ("" == imgData.Name)
                    {
                        // UI�N���X���쐬
                        m_spriteSkill = NewGO<CSpriteUI>();
                        m_spriteSkill->LoadSprite("�t�@�C���p�X");
                        // �|�W�V���������[�h�����摜�Ɠ����ɂ���
                        m_spriteSkill->SetPosition(imgData.Position);
                        // �s�{�b�g�����[�h�����摜�Ɠ����ɂ���
                        m_spriteSkill->SetPivot(imgData.Pivot);
                        // �t�b�N�����̂ŁAtrue��Ԃ�
                        return true;
                    }
                });
        }

        void CSkillIconUI::OnDestroy()
        {
            DeleteGO(m_spriteBase);
            DeleteGO(m_spriteSkill);
        }

        void CSkillIconUI::Update(float deltaTime)
        {
            // ���t���[���̏�����������

        }

        void CSkillIconUI::Animation()
        {

        }
    }
}