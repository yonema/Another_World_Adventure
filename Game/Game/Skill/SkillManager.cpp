#include "YonemaEnginePreCompile.h"
#include "SkillManager.h"
#include "../Player/Player.h"
#include "ActiveSkillList.h"
#include "ActiveSkill.h"

namespace nsAWA {

	namespace nsSkill {

		void CSkillManager::FindPlayer() {

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			if (player != nullptr) {

				m_player = player;
			}
			else {

				nsGameWindow::MessageBoxWarning(L"CSkillManager : player ��������܂���ł����B");
			}
		}

		void CSkillManager::SetActiveSkill(int setNum, const std::string& activeSkillName) {

			if (m_player == nullptr) {

				FindPlayer();

				//�v���C���[��������Ȃ��Ȃ瑁�����^�[���B
				if (m_player == nullptr) { return; }
			}

			//�ݒ�ԍ����`�F�b�N�B
			if (setNum >= CActiveSkill::m_kActiveSkillNumMax) {

				nsGameWindow::MessageBoxError(L"�A�N�e�B�u�X�L���̐ݒ�ԍ����K�萔�𒴂��Ă��܂��B");
			}

			//���O����A�N�e�B�u�X�L���𐶐��B
			CActiveSkillBuilder activeSkillBuilder;
			CActiveSkill* activeSkill =  activeSkillBuilder.CreateActiveSkill(activeSkillName);

			//�v���C���[�ɃA�N�e�B�u�X�L����ݒ�B
			m_player->SetActiveSkill(setNum, activeSkill);
		}
	}
}