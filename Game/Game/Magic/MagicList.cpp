#include "YonemaEnginePreCompile.h"
#include "MagicList.h"
#include "../CSV/CSVManager.h"
#include "MagicBallOne.h"
#include "MagicBallSide.h"
#include "MagicBallForward.h"

namespace nsAWA {

	namespace nsMagic {

		namespace {

			constexpr const wchar_t* kMagicListCSVFilePath = L"Assets/CSV/MagicList.csv";	//���@�̃��X�g��CSV�̃t�@�C���p�X	
		}

		void CMagicList::LoadMagicList() {

			//CSV�����[�h�B
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kMagicListCSVFilePath);

			//���@�f�[�^�̐��`�𐶐��B
			SMagicData magicDataBase;

			//���@�f�[�^���擾�B
			auto magicDataStr = csvManager.GetCsvData();

			//���@�f�[�^�����ɎQ�ƁB
			for (auto& lineData : magicDataStr) {

				//���o�����擾�B
				std::string title = lineData[0];

				if (title == "*") {

					//���̏I�[�Ȃ̂ŏ���ǉ��B

					//�f�[�^���i�[�B
					m_magicList.emplace_back(magicDataBase);

					//���@�f�[�^�̐��`���������B
					SMagicData clearData;
					magicDataBase = clearData;

					//���ցB
					continue;
				}

				//���@�f�[�^���擾�B
				if (title == "NAME") {

					magicDataBase.name = lineData[1];
				}
				else if(title == "TYPE") {

					magicDataBase.magicType = lineData[1];
				}
				else if (title == "FEATURE") {

					lineData.erase(lineData.begin());
					magicDataBase.featureList.emplace_back(lineData);
				}
			}
		}

		const CMagicList::SMagicData& CMagicList::GetMagicData(const std::string& name)const {

			//���@���X�g�����ɎQ�ƁB
			for (const auto& magic : m_magicList) {

				//�������O�̖��@������������B
				if (magic.name == name) {

					//���̖��@�̏������^�[���B
					return magic;
				}
			}

			//�G���[�o�́B
			std::string errorMsg = "CMagicList : ���@��������܂���ł����B : ";
			errorMsg += name;
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

			std::abort();
		}

		CMagicBase* CMagicBuilder::CreateMagic(const std::string& magicName) {

			//���@���X�g�̃C���X�^���X���擾�B
			auto magicList = CMagicList::GetInstance();

			//���O���疂�@�̏����擾�B
			CMagicList::SMagicData magicData = magicList->GetMagicData(magicName);

			//���@�^�C�v���擾�B
			std::string magicType = magicData.magicType;

			CMagicBase* magic = nullptr;

			//���@�𐶐��B
			if (magicType == "One") {

				magic = NewGO<CMagicBallOne>();
			}
			else if (magicType == "Side") {

				magic = NewGO<CMagicBallSide>();
			}
			else if (magicType == "Forward") {

				magic = NewGO<CMagicBallForward>();
			}

			//���O��ݒ�B
			magic->SetMagicName(magicData.name);

			//���ʂ̃��X�g��ݒ�B
			magic->SetFeatureList(magicData.featureList);

			return magic;
		}
	}
}