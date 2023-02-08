#include "YonemaEnginePreCompile.h"
#include "PassiveSkillList.h"
#include "PassiveSkill.h"
#include "../CSV/CSVManager.h"
#include "../Feature/FeatureBuilder.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr const wchar_t* kPassiveSkillCSVFilePath = L"Assets/CSV/Player/PassiveSkillList.csv";	//�p�b�V�u�X�L����CSV�t�@�C���p�X
		}

		void CPassiveSkillList::LoadPassiveSkillList() {

			//�p�b�V�u�X�L���̃��X�g��CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kPassiveSkillCSVFilePath);
			auto passiveSkillData = csvManager.GetCsvData();

			SPassiveSkillData passiveSkillDataBase;

			//�A�N�e�B�u�X�L���̃f�[�^�����ɎQ�ƁB
			for (auto& lineData : passiveSkillData) {

				//���o�����擾�B
				std::string title = lineData[0];

				//��؂�Ȃ�B
				if (title == "*") {

					//�p�b�V�u�X�L���̏������X�g�ɒǉ��B
					m_passiveSkillList.emplace_back(passiveSkillDataBase);

					//�f�[�^���������B
					SPassiveSkillData clearData;
					passiveSkillDataBase = clearData;

					//���ցB
					continue;
				}
				else if (title == "NAME") {

					//���O���擾�B
					std::string name = lineData[1];
					passiveSkillDataBase.name = name;

				}
				else if (title == "FEATURE") {

					//���ʂ̃��X�g���擾�B
					lineData.erase(lineData.begin());
					passiveSkillDataBase.featureList.emplace_back(lineData);
				}
				else {

					//�G���[�o�́B
					std::string errorMsg = "CPassiveSkill : CSV�f�[�^�̃^�C�g����񂪕s�K�؂ł��B : ";
					errorMsg += title;
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

					std::abort();
				}
			}
		}

		const SPassiveSkillData& CPassiveSkillList::GetPassiveSkillData(const std::string& passiveSkillName) {

			//�p�b�V�u�X�L���̃��X�g�����ɎQ�ƁB
			for (const auto& passiveSkillData : m_passiveSkillList) {

				//�������O�̃p�b�V�u�X�L��������������B
				if (passiveSkillData.name == passiveSkillName) {

					//���̃f�[�^�����^�[���B
					return passiveSkillData;
				}
			}

			//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
			std::string errorMsg = "�������ꂽ���O�����X�g�ɂ���܂���B : ";
			errorMsg += passiveSkillName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();

		}

		CPassiveSkill* CPassiveSkillBuilder::CreatePassiveSkill(const std::string& passiveSkillName) {

			//���O����A�N�e�B�u�X�L���̃f�[�^���擾�B
			SPassiveSkillData passiveSkillData = CPassiveSkillList::GetInstance()->GetPassiveSkillData(passiveSkillName);

			//�p�b�V�u�X�L���𐶐��B
			CPassiveSkill* passiveSkill = new CPassiveSkill;

			//�e��ݒ�B
			passiveSkill->SetName(passiveSkillData.name);
			passiveSkill->SetFeatureListStr(passiveSkillData.featureList);

			//���������p�b�V�u�X�L�������^�[���B
			return passiveSkill;
		}
	}
}