#include "YonemaEnginePreCompile.h"
#include "AllItemList.h"
#include "../CSV/CSVManager.h"
#include "../Utils/StringManipulation.h"
#include "SelfItem.h"
#include "ThrowItem.h"

#include "../Feature/HealFeature.h"
#include "../Feature/ApplyDamageFeature.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const wchar_t* const kItemCSVFilePath = L"Assets/CSV/test.csv";	//�A�C�e����񂪓�����CSV�t�@�C���̃t�@�C���p�X
			constexpr const char* const kItemInfoDelimiter = "*";	//�A�C�e�����̋�؂�
		}

		void CAllItemList::LoadAllItemList() {

			//CSV�Ǘ��N���X�𐶐��B
			nsCSV::CCsvManager csvManager;

			//�A�C�e����񂪓�����csv�t�@�C�������[�h�B
			csvManager.LoadCSV(kItemCSVFilePath);

			//�A�C�e�����𐶐��B
			CreateItemInfo(csvManager.GetCsvData());
		}

		void CAllItemList::CreateItemInfo(std::list<std::vector<std::string>> itemInfo) {

			//�A�C�e�����l�����邽�߂ɕK�v�ȉ������������B

			SItemInfo itemInfoBase;					//���̃A�C�e�����
			std::string title;						//csv������͂������̃^�C�g��
			std::vector<std::string> featureInfo;	//���̌��ʂ̔z��
			bool addFeature = false;				//���ʂ��ǉ����ꂽ���ǂ����̃t���O

			//���𒲂ׂ�B
			for (const auto& lineData : itemInfo) {

				//����ɏڂ����l�𒲂ׂ�B
				for (const auto& detail : lineData) {

					//��؂�̍��}�������Ă�����B
					if (detail == kItemInfoDelimiter) {

						//�ǉ��̃A�C�e����񂪂Ȃ��Ƃ��āA�A�C�e����ǉ�����B
						m_allItemList.emplace_back(itemInfoBase);

						//���̃A�C�e�������������B
						ClearItemInfoBase(itemInfoBase);

						//���ցB
						continue;
					}

					//���ꂩ�牽�����͂���Ă���̂����O�ɒ��ׂĈꎞ�ۑ��B
					if (detail == "NAME" || detail == "TYPE" || detail == "FEATURE") {

						//���̃^�C�g����ۑ��B
						title = detail;

						//���ցB
						continue;
					}

					//�^�C�g����NAME��������B
					if (title == "NAME") {

						//���O��ݒ�B
						itemInfoBase.name = detail;

						//���ցB
						continue;
					}

					//�^�C�g����TYPE��������B
					if (title == "TYPE") {

						//�A�C�e���̃^�C�v��ݒ�B
						itemInfoBase.itemType = detail;

						//���ցB
						continue;
					}

					//�^�C�g����FEATURE��������B
					if (title == "FEATURE") {

						//�z��Ɍ��ʂ����ǉ��B
						featureInfo.emplace_back(detail);

						//�ǉ����ꂽ�B
						addFeature = true;

						//���ցB
						continue;
					}
				}

				//���̍s�Ō��ʂ����ǉ�����Ă�����B
				if (addFeature) {

					//�A�C�e���Ɍ��ʂ�ǉ��B
					itemInfoBase.featureList.emplace_back(featureInfo);

					//���̔z����������B
					featureInfo.clear();

					//�t���O���������B
					addFeature = false;
				}
			}
		}

		void CAllItemList::ClearItemInfoBase(SItemInfo& itemInfoBase) {

			//���̃A�C�e�������������B
			SItemInfo itemInfoBaseInit;
			itemInfoBase = itemInfoBaseInit;
		}

		bool CAllItemList::IsFoundName(std::string itemName) {

			//�������O�����邩���X�g���珇�Ɍ����B
			for (const auto& itemInfo : m_allItemList) {

				//�������O�̃A�C�e�������������B
				if (itemInfo.name == itemName) {

					//���������̂�true�B
					return true;
				}
			}

			//���O�����X�g�ɑ��݂��Ă��Ȃ��̂Ōx�����o�́B
			std::string errorMsg = "�������ꂽ���O�����X�g�ɂ���܂���B : ";
			errorMsg += itemName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());

			//������Ȃ������̂�false�B
			return false;
		}

		const SItemInfo& CAllItemList::GetItemInfo(std::string itemName) {

			//���X�g���疼�O����������B
			for (const auto& itemInfo : m_allItemList) {

				//�������O�̃A�C�e�������������B
				if (itemInfo.name == itemName) {

					//���̃A�C�e���̏������^�[���B
					return itemInfo;
				}
			}

			//������Ȃ������B
			std::string errorMsg = "���̖��O�̃A�C�e����������܂���ł����B : ";
			errorMsg += itemName;

			//�x���E�B���h�E���o�́B
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

			//��������������ʂ��Ă͂����Ȃ����A��̏������^�[���B
			return m_itemList;
		}

		CItem* CItemBuilder::CreateItemBase(std::string itemName) {

			//���X�g����A�C�e�����������A�����擾����B
			SItemInfo itemInfo = CAllItemList::GetInstance()->GetItemInfo(itemName);

			//�A�C�e���̐��`���������B
			CItem* item = nullptr;

			//�^�C�v��Self��������B
			if (itemInfo.itemType == "Self") {

				//���g�ɕt�^����^�C�v�̃A�C�e���𐶐��B
				item = NewGO<CSelfItem>();
			}
			else if (itemInfo.itemType == "Throw") {

				//������^�C�v�̃A�C�e���𐶐��B
				item = NewGO<CThrowItem>();
			}

			//�A�C�e������ݒ�B
			item->SetItemInfo(itemInfo);

			//�������ꂽ�A�C�e�������^�[���B
			return item;
		}
	}
}