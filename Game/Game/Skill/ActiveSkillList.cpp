#include "YonemaEnginePreCompile.h"
#include "ActiveSkillList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr const wchar_t* kActiveSkillCSVFilePath = L"Assets/CSV/Player/ActiveSkillList.csv";	//�A�N�e�B�u�X�L����CSV�t�@�C���p�X
			constexpr const wchar_t* kActiveSkillAnimationEventCSVFilePath = L"Assets/CSV/Player/ActiveSkillAnimationEventList.csv";	//�A�N�e�B�u�X�L���̃A�j���[�V�����C�x���g��CSV�t�@�C���p�X
		}

		void CActiveSkillList::LoadActiveSkillList() {

			//�A�N�e�B�u�X�L���̃��X�g��CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kActiveSkillCSVFilePath);
			std::list<std::vector<std::string>> activeSkillDataStr = csvManager.GetCsvData();

			//�A�N�e�B�u�X�L���̃f�[�^�����ɎQ�ƁB
			for (const auto& lineData : activeSkillDataStr) {

				//�X�L���^�C�v���擾�B
				std::string type = lineData[0];

				//���O���擾�B
				std::string name = lineData[1];

				//����MP���擾�B
				float useMP = std::stof(lineData[2]);

				//�A�j���[�V�����̃t�@�C���p�X���擾�B
				std::string animFilePath = lineData[3];

				//�A�N�e�B�u�X�L���̃f�[�^��ݒ�B
				SActiveSkillData activeSkillData;
				activeSkillData.type = type;
				activeSkillData.name = name;
				activeSkillData.useMP = useMP;
				activeSkillData.animFilePath= animFilePath;

				//�A�N�e�B�u�X�L���̃f�[�^�����X�g�ɒǉ��B
				AddActiveSkill(activeSkillData);
			}

			//�A�N�e�B�u�X�L���̃A�j���[�V�����C�x���g�̃��X�g��CSV�����[�h�B
			csvManager.ClearCSV();
			csvManager.LoadCSV(kActiveSkillAnimationEventCSVFilePath);
			std::list<std::vector<std::string>> activeSkillAnimationEventDataStr = csvManager.GetCsvData();

			std::list<CActiveSkill::SActiveSkillAnimData> activeSkillAnimDataList;
			CActiveSkill::SActiveSkillAnimData activeSkillAnimDataBase;
			std::list<std::vector<std::string>> animEventFeatureData;

			//�A�j���[�V�����C�x���g�̃��X�g�����ɎQ�ƁB
			for (const auto& animEventData : activeSkillAnimationEventDataStr) {

				//���o�����擾�B
				std::string title = animEventData[0];

				if (title == "*") {

					//�A�j���[�V�����C�x���g�̏ڍׂ�ǉ��B
					activeSkillAnimDataBase.sAnimEventData = animEventFeatureData;

					//�ڍׂ��������B
					std::list<std::vector<std::string>> initFeatureData;
					animEventFeatureData = initFeatureData;

					activeSkillAnimDataList.emplace_back(activeSkillAnimDataBase);
					CActiveSkill::SActiveSkillAnimData initData;
					activeSkillAnimDataBase = initData;

					//���ցB
					continue;
				}

				if (title == "NAME") {

					activeSkillAnimDataBase.skillName = animEventData[1];
					
					//���ցB
					continue;
				}
				else if (title == "INDEX") {

					activeSkillAnimDataBase.index = animEventData[1];

					//���ցB
					continue;
				}
				else {

					animEventFeatureData.emplace_back(animEventData);

					//���ցB
					continue;
				}
			}

			//�X�L���f�[�^�ɃA�j���[�V�����f�[�^��ǉ����邽�߁A���X�g���Ƃ炵���킹��B
			for (auto& skillList : m_activeSkillList) {

				for (const auto& skillAnim : activeSkillAnimDataList) {

					//�������O�̃X�L���A�j���[�V�����f�[�^������������R�s�[�B
					if (skillList.name == skillAnim.skillName) {

						skillList.animDataList.emplace_back(skillAnim);
					}
				}
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
			activeSkill->SetAnimaitonFilePath(activeSkillData.animFilePath);
			activeSkill->SetAnimDataList(activeSkillData.animDataList);

			//���������A�N�e�B�u�X�L�������^�[���B
			return activeSkill;
		}
	}
}