#include "YonemaEnginePreCompile.h"
#include "MaterialItemList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const wchar_t* kMaterialItemListCSVFilePath = L"Assets/CSV/MaterialItemList.csv";
		}

		void CMaterialItemList::LoadMaterialItemList() {

			//�f�ރA�C�e�����X�g��CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kMaterialItemListCSVFilePath);

			SMaterialItemInfo materialItemInfoBase;	//���̑f�ރA�C�e�����
			

			//���𒲂ׂ�B
			for (const auto& lineData : csvManager.GetCsvData()) {

				//���o�����擾�B
				std::string title = lineData[0];

				//��؂�̍��}�������Ă�����B
				if (title == "*") {

					//�ǉ��̃A�C�e����񂪂Ȃ��Ƃ��āA�A�C�e����ǉ�����B
					m_materialItemList.emplace_back(materialItemInfoBase);

					//���̃A�C�e�������������B
					SMaterialItemInfo itemInfoBaseInit;
					materialItemInfoBase = itemInfoBaseInit;

					//���ցB
					continue;
				}

				//�^�C�g����NAME��������B
				if (title == "NAME") {

					//���O��ݒ�B
					materialItemInfoBase.name = lineData[1];

					//���ցB
					continue;
				}

				//�^�C�g����RANK��������B
				if (title == "RANK") {

					//�A�C�e���̃^�C�v��ݒ�B
					materialItemInfoBase.rank = lineData[1];

					//���ցB
					continue;
				}
			}
		}

		const SMaterialItemInfo& CMaterialItemList::GetMaterialItemInfo(const std::string& itemName) {

			//���X�g���疼�O����������B
			for (const auto& materialItemInfo : m_materialItemList) {

				//�������O�̃A�C�e�������������B
				if (materialItemInfo.name == itemName) {

					//���̃A�C�e���̏������^�[���B
					return materialItemInfo;
				}
			}

			//������Ȃ������B
			std::string errorMsg = "���̖��O�̑f�ރA�C�e����������܂���ł����B : ";
			errorMsg += itemName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}

		bool CMaterialItemList::IsFoundName(std::string itemName) {

			//�������O�����邩���X�g���珇�Ɍ����B
			for (const auto& materialItem : m_materialItemList) {

				//�������O�̑f�ރA�C�e�������������B
				if (materialItem.name == itemName) {

					//���������̂�true�B
					return true;
				}
			}

			//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
			std::string errorMsg = "CMaterialItemList : �������ꂽ�f�ރA�C�e�������X�g�ɂ���܂���B : ";
			errorMsg += itemName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());

			//������Ȃ������̂�false�B
			return false;
		}
	}
}