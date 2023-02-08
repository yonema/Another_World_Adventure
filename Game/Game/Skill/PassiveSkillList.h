#pragma once
namespace nsAWA {

	namespace nsSkill {

		//�O���錾
		class CPassiveSkill;

		//�p�b�V�u�X�L���̃f�[�^
		struct SPassiveSkillData {

			std::string name = "NoName";	//���O
			std::list<std::vector<std::string>> featureList;	//���ʂ̃��X�g
		};
		//�p�b�V�u�X�L�����X�g
		class CPassiveSkillList : nsUtils::SNoncopyable
		{
		public:
			static CPassiveSkillList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CPassiveSkillList* passiveSkillList = new CPassiveSkillList;

				return passiveSkillList;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadPassiveSkillList();

			const SPassiveSkillData& GetPassiveSkillData(const std::string& passiveSkillName);

		private:
			std::list<SPassiveSkillData> m_passiveSkillList;	//�p�b�V�u�X�L���̃��X�g
		};

		//�p�b�V�u�X�L�������N���X
		class CPassiveSkillBuilder : nsUtils::SNoncopyable {

		public:
			CPassiveSkill* CreatePassiveSkill(const std::string& passiveSkillName);
		};
	}
}

