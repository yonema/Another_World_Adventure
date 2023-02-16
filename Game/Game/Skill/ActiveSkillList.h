#pragma once
#include "ActiveSkill.h"

namespace nsAWA {

	namespace nsSkill {

		//�A�N�e�B�u�X�L���̃f�[�^
		struct SActiveSkillData {

			std::string type = "NoType";	//�X�L���^�C�v
			std::string name = "NoName";	//���O
			std::string animFilePath = "NoPath";	//�A�j���[�V�����̃t�@�C���p�X
			float useMP = 0.0f;				//����MP
			std::string effectName = "NoPath";	//�G�t�F�N�g�̖��O
			std::list<CActiveSkill::SActiveSkillAnimData> animDataList;	//�A�j���[�V�����f�[�^���X�g
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

			const std::list<SActiveSkillData>& GetActiveSkillData() {

				//�A�N�e�B�u�X�L���̃��X�g���擾�B
				return m_activeSkillList;
			}

			constexpr const auto& GetActiveSkillList() const noexcept
			{
				return m_activeSkillList;
			}

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