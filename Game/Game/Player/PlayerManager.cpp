#include "YonemaEnginePreCompile.h"
#include "PlayerManager.h"
#include "Player.h"
#include "../Skill/ActiveSkillList.h"
#include "../Skill/ActiveSkill.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

namespace nsAWA {

	namespace nsPlayer {

		bool CPlayerManager::FindPlayer() {

			//���Ƀv���C���[���������Ă���Ȃ�B
			if (m_player != nullptr) {

				//�����B
				return true;
			}

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			if (player != nullptr) {

				//�v���C���[�𔭌��B
				m_player = player;

				//�����B
				return true;
			}
			else {

				//�v���C���[��������Ȃ������B
				return false;
			}
		}

		void CPlayerManager::SetActiveSkill(int setNum, const std::string& activeSkillName) {

			//�ݒ�ԍ����`�F�b�N�B
			if (setNum >= nsSkill::CActiveSkill::m_kActiveSkillNumMax) {

				nsGameWindow::MessageBoxError(L"�A�N�e�B�u�X�L���̐ݒ�ԍ����K�萔�𒴂��Ă��܂��B");
			}

			//���O����A�N�e�B�u�X�L���𐶐��B
			nsSkill::CActiveSkillBuilder activeSkillBuilder;
			nsSkill::CActiveSkill* activeSkill =  activeSkillBuilder.CreateActiveSkill(activeSkillName);

			//�v���C���[�ɃA�N�e�B�u�X�L����ݒ�B
			m_player->SetActiveSkill(setNum, activeSkill);
		}

		void CPlayerManager::SetWeapon(const std::string& weaponName) {

			//����\�z�N���X�𐶐��B
			nsWeapon::CWeaponBuilder weaponBuilder;

			//����𐶐��B
			nsWeapon::CWeapon* weapon = weaponBuilder.CreateWeapon(weaponName);

			//�����ݒ�B
			m_player->SetWeapon(weapon);
		}

		void CPlayerManager::SetArmor(const std::string& armorName) {

			//�h��\�z�N���X�𐶐��B
			nsArmor::CArmorBuilder armorBuilder;

			//�h��𐶐��B
			nsArmor::CArmor* armor = armorBuilder.CreateArmor(armorName);

			//�h���ݒ�B
			m_player->SetArmor(armor);
		}
	}
}