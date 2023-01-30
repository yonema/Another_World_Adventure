#include "YonemaEnginePreCompile.h"
#include "WeaponList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsWeapon {

		namespace {

			constexpr const wchar_t* kWeaponCSVFilePath = L"Assets/CSV/Player/PlayerWeapon.csv";	//����̃��X�g��CSV�̃t�@�C���p�X
		}

		void CWeaponList::LoadWeaponList() {

			//����̃��X�g�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kWeaponCSVFilePath);

			SWeaponInfo weaponInfo;

			//����̃f�[�^�����Ɏ擾�B
			for (const auto& lineData : csvManager.GetCsvData()) {

				//���o�����擾�B
				std::string title = lineData[0];

				//��؂�Ȃ�B
				if (title == "*") {

					//�f�[�^�����X�g�ɒǉ��B
					m_weaponDataList.emplace_back(weaponInfo);

					//�f�[�^���������B
					SWeaponInfo clearInfo;
					weaponInfo = clearInfo;

					//���ցB
					continue;
				}

				if (title == "NAME") {

					std::string name = lineData[1];

					//���O��ݒ�B
					weaponInfo.name = name;

					//���f���̃t�@�C���p�X��ݒ�B
					weaponInfo.modelFilePath = "Assets/Models/Weapons/";
					weaponInfo.modelFilePath += name;
					weaponInfo.modelFilePath += ".fbx";
				}
				else if (title == "TYPE") {

					std::string type = lineData[1];

					if (type == "Sword") {

						weaponInfo.weaponType = EnWeaponType::enSword;
					}
					else if (type == "Axe") {

						weaponInfo.weaponType = EnWeaponType::enAxe;
					}
					else if (type == "Wand") {

						weaponInfo.weaponType = EnWeaponType::enWand;
					}
					else {

						//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
						std::string errorMsg = "CWeaponList : �^�C�v�̐ݒ肪�s�K�؂ł��B";
						errorMsg += type;

						//�x���E�B���h�E���o�́B
						nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
						std::abort();
					}
				}
				else if (title == "ATK") {

					//�����U���͂�ݒ�B
					weaponInfo.attack = std::stof(lineData[1]);
				}
				else if (title == "INT") {

					//���@�U���͂�ݒ�B
					weaponInfo.intelligence = std::stof(lineData[1]);
				}
				else if (title == "CRI") {

					//�N���e�B�J������ݒ�B
					weaponInfo.critical = std::stof(lineData[1]);
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

		const SWeaponInfo& CWeaponList::GetWeaponData(const std::string& weaponName) {

			//����̃��X�g�����ɎQ�ƁB
			for (const auto& weaponData : m_weaponDataList) {

				//�������O�̕��킪����������B
				if (weaponData.name == weaponName) {

					//���̃f�[�^�����^�[���B
					return weaponData;
				}
			}

			//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
			std::string errorMsg = "CWeaponList : �������ꂽ���O�����X�g�ɂ���܂���B : ";
			errorMsg += weaponName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}
	}
}