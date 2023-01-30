#include "YonemaEnginePreCompile.h"
#include "ActiveSkillList.h"
#include "../CSV/CSVManager.h"
#include "../Skill/ActiveSkill.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr const wchar_t* kActiveSkillCSVFilePath = L"Assets/CSV/Player/ActiveSkillList.csv";	//�A�N�e�B�u�X�L����CSV�t�@�C���p�X
		}

		void CActiveSkillList::LoadActiveSkillList() {

			//�A�N�e�B�u�X�L���̃��X�g��CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kActiveSkillCSVFilePath);

			//�A�N�e�B�u�X�L���̃f�[�^�����ɎQ�ƁB
			for (const auto& lineData : csvManager.GetCsvData()) {

				//���O���擾�B
				std::string name = lineData[0];

				//����MP���擾�B
				int useMP = std::stoi(lineData[1]);

				//�A�N�e�B�u�X�L���̃f�[�^��ݒ�B
				SActiveSkillData activeSkillData;
				activeSkillData.name = name;
				activeSkillData.useMP = useMP;

				//�A�N�e�B�u�X�L���̃f�[�^�����X�g�ɒǉ��B
				AddActiveSkill(activeSkillData);
			}
		}

		const SActiveSkillData& CActiveSkillList::GetActiveSkillData(const std::string& activeSkillName) {

			//�A�N�e�B�u�X�L���̃��X�g�����ɎQ�ƁB
			for (const auto& activeSkillData : m_activeSkillList) {

				//�������O�̃A�N�e�B�u�X�L��������������B
				if (activeSkillData.name == activeSkillName) {

					//���̃f�[�^�����^�[���B
					return activeSkillData;
				}
			}

			//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
			std::string errorMsg = "�������ꂽ���O�����X�g�ɂ���܂���B : ";
			errorMsg += activeSkillName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}

		CActiveSkill* CActiveSkillBuilder::CreateActiveSkill(const std::string& activeSkillName) {

			//���O����A�N�e�B�u�X�L���̃f�[�^���擾�B
			SActiveSkillData activeSkillData = CActiveSkillList::GetInstance()->GetActiveSkillData(activeSkillName);

			//�A�N�e�B�u�X�L���𐶐��B
			CActiveSkill* activeSkill = new CActiveSkill;

			//�e��ݒ�B
			activeSkill->SetName(activeSkillData.name);
			activeSkill->SetUseMP(activeSkillData.useMP);

			//���������A�N�e�B�u�X�L�������^�[���B
			return activeSkill;
		}
	}
}