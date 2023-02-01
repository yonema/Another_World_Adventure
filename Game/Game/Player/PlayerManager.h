#pragma once
#include "../Skill/ActiveSkillList.h"

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;

		//�v���C���[�Ǘ��N���X
		class CPlayerManager : nsUtils::SNoncopyable
		{
		public:

			static CPlayerManager* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CPlayerManager* instance = new CPlayerManager;

				//�C���X�^���X���擾�B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			bool FindPlayer();

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

			std::list<nsSkill::SActiveSkillData> GetCanUseActiveSkillList();
			
			void SetWeapon(const std::string& weaponName);

			void SetArmor(const std::string& armorName);

			void AddCanUseActiveSkill(const std::string& skillName) {

				//�g�p�\�ȃA�N�e�B�u�X�L�������X�g���珇�ɎQ�ƁB
				for (const auto& activeSkillData : m_canUseActiveSkillDataList) {

					//�������O�̃X�L��������Ȃ�B
					if (activeSkillData.name == skillName) {

						//�ǉ�����K�v���Ȃ��̂ŏI���B
						return;
					}
				}
				
				//���O����A�N�e�B�u�X�L���̃f�[�^���擾�B
				nsSkill::SActiveSkillData activeSkillData = nsSkill::CActiveSkillList::GetInstance()->GetActiveSkillData(skillName);

				//�g�p�\�ȃA�N�e�B�u�X�L���̃f�[�^�����X�g�ɒǉ��B
				m_canUseActiveSkillDataList.emplace_back(activeSkillData);
			}

		private:
			void ResetActiveSkill();

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//�v���C���[�̃|�C���^
			std::list<nsSkill::SActiveSkillData> m_canUseActiveSkillDataList;	//�g�p�\�ȃA�N�e�B�u�X�L���̖��O�̃��X�g
		};
	}
}