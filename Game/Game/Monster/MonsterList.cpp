#include "MonsterList.h"
#include "Monster.h"
#include "../CSV/CSVManager.h"
#include "../Utils/StringManipulation.h"
#include "MonsterAnimation.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

			constexpr const wchar_t* const kMonsterNameCSVFilePath = L"Assets/CSV/Monsters/MonsterList.csv";		//�����X�^�[�̖��O�̃��X�g��CSV�̃t�@�C���p�X
		}

		void CMonsterList::CreateMonsterList() {

			//�����X�^�[�̖��O�̃��X�g��ǂݍ��ށB
			nsCSV::CCsvManager monsterNameCsvManager;
			monsterNameCsvManager.LoadCSV(kMonsterNameCSVFilePath);

			//�����X�^�[�f�[�^�̐��`�𐶐��B
			SMonsterInitData monsterInitData;

			//�����X�^�[�̖��O���烂���X�^�[����ǂݍ��݁A�ێ�����B
			for (const auto& monsterList : monsterNameCsvManager.GetCsvData()) {

				//���o�����擾�B
				std::string title = monsterList[0];

				if (title == "*") {

					//�����X�^�[�f�[�^��ǉ��B
					AddMonsterInitData(monsterInitData);

					//�����X�^�[�f�[�^���������B
					SMonsterInitData monsterInitDataBase;
					monsterInitData = monsterInitDataBase;

					//���ցB
					continue;
				}

				if (title == "NAME") {

					//���O��ݒ�B
					monsterInitData.name = monsterList[1];
				}
				
				if (title == "DROPEXP") {

					//�l���o���l�ʂ�ݒ�B
					monsterInitData.dropExp = std::stoi(monsterList[1]);
				}

				if (title == "DROPITEM") {

					//�h���b�v�A�C�e����ݒ�B
					monsterInitData.dropMaterialItemList.emplace_back(monsterList[1]);
				}

				//���f���̃t�@�C���p�X��ݒ�B
				monsterInitData.modelFilePath = "Assets/Models/Monsters/";
				monsterInitData.modelFilePath += monsterInitData.name;
				monsterInitData.modelFilePath += ".fbx";

				//�A�j���[�V������񂪓�����CSV�t�@�C���̃p�X��ݒ�B
				std::string animCSVFilePath = "Assets/CSV/Monsters/";
				animCSVFilePath += monsterInitData.name + "/";
				animCSVFilePath += monsterInitData.name + "_Animation.csv";

				//�A�j���[�V�����C�x���g��񂪓�����CSV�t�@�C���̃p�X��ݒ�B
				std::string animEventCSVFilePath = "Assets/CSV/Monsters/";
				animEventCSVFilePath += monsterInitData.name + "/";
				animEventCSVFilePath += monsterInitData.name + "_AnimationEvent.csv";

				//�A�j���[�V���������[�h�B
				CMonsterAnimation monsterAnimation;
				monsterAnimation.LoadAnimation(
					monsterInitData.name,
					nsUtils::GetWideStringFromString(animCSVFilePath).c_str(),
					nsUtils::GetWideStringFromString(animEventCSVFilePath).c_str()
				);

				//�A�j���[�V�����f�[�^�̃��X�g���擾�A�ݒ�B
				monsterInitData.animDataList = monsterAnimation.GetAnimDataList();

				//�A�j���[�V�����̃t�@�C���p�X�̃��X�g���擾�A�ݒ�B
				monsterInitData.animationFilePath = monsterAnimation.GetAnimFilePathArray();
			}
		}

		CMonster* CMonsterList::CreateMonster(const std::string& monsterName) {

			CMonster* monster = nullptr;
			//�����X�^�[�̃��X�g�����ɎQ�ƁB
			for (const auto& monsterData : m_monsterDataList) {

				//�������O�̃����X�^�[�������B
				if (monsterData.name == monsterName) {

					//�����X�^�[�𐶐��B
					monster = NewGO<CMonster>(nsMonster::CMonster::m_kObjName_Monster);
					monster->Create(monsterData);
				}
			}

			//�����X�^�[��������Ȃ�������B
			if (monster == nullptr) {

				std::string errMsg = "�����X�^�[�̌����Ɏ��s���܂����B : ";
				errMsg += monsterName;
				nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errMsg).c_str());
			}

			//�����X�^�[�����^�[���B
			return monster;
		}
	}
}