#pragma once

namespace nsAWA {

	namespace nsSkill {

		//�O���錾
		class CActiveSkill;

		//�A�N�e�B�u�X�L���̃f�[�^
		struct SActiveSkillData {

			std::string name = "NoName";	//���O
			int useMP = 0;					//����MP
		};

		//�A�N�e�B�u�X�L���̃��X�g
		class CActiveSkillList : nsUtils::SNoncopyable
		{
		public:
			static CActiveSkillList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CActiveSkillList* activeSkillList = new CActiveSkillList;

				return activeSkillList;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadActiveSkillList();

			const SActiveSkillData& GetActiveSkillData(const std::string& activeSkillName);

		private:
			void AddActiveSkill(const SActiveSkillData& activeSkillData) {

				//�A�N�e�B�u�X�L�������X�g�ɒǉ��B
				m_activeSkillList.emplace_back(activeSkillData);
			}

		private:
			std::list<SActiveSkillData> m_activeSkillList;		//�A�N�e�B�u�X�L���̃��X�g
		};

		//�A�N�e�B�u�X�L�������N���X
		class CActiveSkillBuilder : nsUtils::SNoncopyable {

		public:
			CActiveSkill* CreateActiveSkill(const std::string& activeSkillName);
		};
	}
}