#include "YonemaEnginePreCompile.h"
#include "PlayerSkillChanger.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Skill/ActiveSkill.h"

namespace nsAWA {

	namespace nsPlayer {

		void CPlayerSkillChanger::Init() {

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			//�v���C���[�A�N�V�����N���X���擾�B
			m_playerAction = &(player->GetPlayerAction());
		}

		void CPlayerSkillChanger::SetActiveSkill(int skillNum, const std::string& skillName) {

			//�A�N�e�B�u�X�L���𐶐��B
			nsSkill::CActiveSkill* activeSkill = CreateActiveSkill(skillName);

			//�A�N�e�B�u�X�L����ݒ�B
			m_playerAction->SetActiveSkill(skillNum, activeSkill);
		}

		nsSkill::CActiveSkill* CPlayerSkillChanger::CreateActiveSkill(const std::string skillName) {

			std::string name = "NoName";
			int useMP = 0;

			//���X�g����A�N�e�B�u�X�L�����擾�i�������j�B

			

			//�������ɃA�N�e�B�u�X�L���𐶐��B
			nsSkill::CActiveSkill* activeSkill = new nsSkill::CActiveSkill;
			activeSkill->SetName(name);
			activeSkill->SetUseMP(useMP);

			return activeSkill;
		}
	}
}