#include "YonemaEnginePreCompile.h"
#include "ArmorList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsArmor {

		namespace {

			constexpr const wchar_t* kArmorCSVFilePath = L"Assets/CSV/Player/PlayerArmor.csv";	//�h��̃��X�g��CSV�̃t�@�C���p�X
		}

		void CArmorList::LoadArmorList() {

			//�h��̃��X�g�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kArmorCSVFilePath);

			SArmorInfo armorInfo;

			//�h��̃f�[�^�����Ɏ擾�B
			for (const auto& lineData : csvManager.GetCsvData()) {

				//���o�����擾�B
				std::string title = lineData[0];

				//��؂�Ȃ�B
				if (title == "*") {

					//�f�[�^�����X�g�ɒǉ��B
					m_armorDataList.emplace_back(armorInfo);

					//�f�[�^���������B
					SArmorInfo clearInfo;
					armorInfo = clearInfo;

					//���ցB
					continue;
				}

				if (title == "NAME") {

					std::string name = lineData[1];

					//���O��ݒ�B
					armorInfo.name = name;
				}
				else if (title == "DEF") {

					//�����h��͂�ݒ�B
					armorInfo.defence = std::stof(lineData[1]);
				}
				else if (title == "MND") {

					//���@�h��͂�ݒ�B
					armorInfo.mind = std::stof(lineData[1]);
				}
				else {

					//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
					std::string errorMsg = "CWeaponList : ���o���f�[�^���s�K�؂ł��B";
					errorMsg += title;

					//�x���E�B���h�E���o�́B
					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}
			}
		}

		const SArmorInfo& CArmorList::GetArmorData(const std::string& armorName) {

			//�h��̃��X�g�����ɎQ�ƁB
			for (const auto& armorData : m_armorDataList) {

				//�������O�̖h�����������B
				if (armorData.name == armorName) {

					//���̃f�[�^�����^�[���B
					return armorData;
				}
			}

			//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
			std::string errorMsg = "CArmorList : �������ꂽ���O�����X�g�ɂ���܂���B : ";
			errorMsg += armorName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}
	}
}