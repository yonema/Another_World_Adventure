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

				//�X�L���^�C�v���擾�B
				std::string type = lineData[0];

				//���O���擾�B
				std::string name = lineData[1];

				//����MP���擾�B
				float useMP = std::stof(lineData[2]);

				//�A�N�e�B�u�X�L���̃f�[�^��ݒ�B
				SActiveSkillData activeSkillData;
				activeSkillData.type = type;
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

			//�X�L���^�C�v���擾�B
			CActiveSkill::EnActiveSkillType type = CActiveSkill::EnActiveSkillType::enNone;
			if (activeSkillData.type == "Sword") {

				type = CActiveSkill::EnActiveSkillType::enSword;
			}
			else if (activeSkillData.type == "Axe") {

				type = CActiveSkill::EnActiveSkillType::enAxe;
			}
			else if (activeSkillData.type == "Wand") {

				type = CActiveSkill::EnActiveSkillType::enWand;
			}
			else if (activeSkillData.type == "Magic") {

				type = CActiveSkill::EnActiveSkillType::enMagic;
			}

			//�e��ݒ�B
			activeSkill->SetName(activeSkillData.name);
			activeSkill->SetUseMP(activeSkillData.useMP);
			activeSkill->SetType(type);

			//���������A�N�e�B�u�X�L�������^�[���B
			return activeSkill;
		}
	}
}