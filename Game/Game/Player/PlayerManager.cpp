#include "YonemaEnginePreCompile.h"
#include "PlayerManager.h"
#include "Player.h"
#include "../Skill/ActiveSkillList.h"
#include "../Skill/ActiveSkill.h"
#include "../Skill/PassiveSkillList.h"
#include "../Skill/PassiveSkill.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Feature/FeatureBuilder.h"
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

		void CPlayerManager::SetPlayer(CPlayer* player) {

			//�v���C���[��ݒ�B
			m_player = player;

			//�A�C�e���Ǘ��N���X�̃^�[�Q�b�g��ݒ�B
			m_itemManager.SetTatget(player);
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

		void CPlayerManager::SetPassiveSkill(int setNum, const std::string& passiveSkillName) {

			//�ݒ�ԍ����`�F�b�N�B
			if (setNum >= m_player->GetPassiveSkillManager()->GetPassiveSkillMaxNum()) {

				nsGameWindow::MessageBoxError(L"�p�b�V�u�X�L���̐ݒ�ԍ����K�萔�𒴂��Ă��܂��B");
			}

			//���O����p�b�V�u�X�L���𐶐��B
			nsSkill::CPassiveSkillBuilder passiveSkillBuilder;
			nsSkill::CPassiveSkill* passiveSkill = passiveSkillBuilder.CreatePassiveSkill(passiveSkillName);

			//���X�g������ʂ𐶐��B
			nsFeature::CFeatureBuilder featureBuilder;
			featureBuilder.CreateFeature(m_player, m_player, passiveSkill->GetFeatureListStr(), passiveSkill->GetFeatureList());

			//�v���C���[�Ƀp�b�V�u�X�L����ݒ�B
			m_player->GetPassiveSkillManager()->SetPassiveSkill(setNum, passiveSkill);
		}

		std::list<nsSkill::SActiveSkillData> CPlayerManager::GetCanUseActiveSkillList() {

			//�g�p�\�ȃA�N�e�B�u�X�L���̃��X�g���`�B
			std::list<nsSkill::SActiveSkillData> canUseActiveSkillList;

			//�������擾�B
			nsWeapon::EnWeaponType type = m_player->GetWeapon()->GetWeaponType();
			std::string typeName = "NoTypeName";

			switch (type) {

			case nsWeapon::EnWeaponType::enSword:
				typeName = "Sword";
				break;
			case nsWeapon::EnWeaponType::enAxe:
				typeName = "Axe";
				break;
			case nsWeapon::EnWeaponType::enWand:
				typeName = "Wand";
				break;
			}

			for (const auto& activeSkill : m_canUseActiveSkillDataList) {

				//�����ƃ^�C�v�������Ă��邩�A���@�X�L���Ȃ�B
				if (activeSkill.type == typeName || activeSkill.type == "Magic") {

					//�g����A�N�e�B�u�X�L���Ƃ��Đݒ�B
					canUseActiveSkillList.emplace_back(activeSkill);
				}
			}

			//�g����A�N�e�B�u�X�L���̃f�[�^�����^�[���B
			return canUseActiveSkillList;
		}

		void CPlayerManager::ResetActiveSkill() {

			//�������擾�B
			nsWeapon::EnWeaponType weaponType = m_player->GetWeapon()->GetWeaponType();

			//����킩��^�C�v���`�B
			nsSkill::CActiveSkill::EnActiveSkillType activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enNone;

			switch (weaponType) {

			case nsWeapon::EnWeaponType::enSword:
				activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enSword;
				break;
			case nsWeapon::EnWeaponType::enAxe:
				activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enAxe;
				break;
			case nsWeapon::EnWeaponType::enWand:
				activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enWand;
				break;
			}

			//�A�N�e�B�u�X�L�������ɎQ�ƁB
			for (int activeSkillNum = 0; activeSkillNum < nsSkill::CActiveSkill::m_kActiveSkillNumMax; activeSkillNum++) {

				//�A�N�e�B�u�X�L�����擾�B
				nsSkill::CActiveSkill* activeSkill = m_player->GetActiveSkill(activeSkillNum);

				//�A�N�e�B�u�X�L�����ݒ肳��Ă��Ȃ�������B
				if (activeSkill == nullptr) {

					//���ցB
					continue;
				}

				//�ݒ蒆�̃A�N�e�B�u�X�L�������@�X�L������Ȃ��A
				//�����ƈ�v���Ă��Ȃ�������B
				if (activeSkill->GetType() != nsSkill::CActiveSkill::EnActiveSkillType::enMagic
					&& activeSkillType != activeSkill->GetType()) {

					//���̃A�N�e�B�u�X�L�����O���B
					m_player->SetActiveSkill(activeSkillNum, nullptr);
				}
			}
		}

		void CPlayerManager::SetWeapon(const std::string& weaponName) {

			//����\�z�N���X�𐶐��B
			nsWeapon::CWeaponBuilder weaponBuilder;

			//����𐶐��B
			nsWeapon::CWeapon* weapon = weaponBuilder.CreateWeapon(weaponName);

			//�����ݒ�B
			m_player->SetWeapon(weapon);

			//�A�N�e�B�u�X�L���̐ݒ���X�V�B
			ResetActiveSkill();
		}

		void CPlayerManager::SetArmor(const std::string& armorName) {

			//�h��\�z�N���X�𐶐��B
			nsArmor::CArmorBuilder armorBuilder;

			//�h��𐶐��B
			nsArmor::CArmor* armor = armorBuilder.CreateArmor(armorName);

			//�h���ݒ�B
			m_player->SetArmor(armor);
		}

		const std::string& CPlayerManager::GetActiveSkillName(const int skillNam)
		{
			if (false == FindPlayer()) {
				nsGameWindow::MessageBoxWarning(L"CPlayerManager : player ��������܂���ł����B");
			}

			return m_player->GetActiveSkill(skillNam)->GetName();
		}
	}
}