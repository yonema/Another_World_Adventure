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

			//�����X�^�[�̖��O���烂���X�^�[����ǂݍ��݁A�ێ�����B
			for (const auto& monsterList : monsterNameCsvManager.GetCsvData()) {

				for (const auto& monsterName : monsterList) {

					//�����X�^�[�f�[�^�̐��`�𐶐��B
					SMonsterInitData monsterInitData;

					//���O��ݒ�B
					monsterInitData.name = monsterName;

					monsterInitData.modelFilePath = "Assets/Models/Monsters/";
					monsterInitData.modelFilePath += monsterName;
					monsterInitData.modelFilePath += ".fbx";

					//�A�j���[�V������񂪓�����CSV�t�@�C���̃p�X��ݒ�B
					std::string animCSVFilePath = "Assets/CSV/Monsters/";
					animCSVFilePath += monsterName + "/";
					animCSVFilePath += monsterName + "_Animation.csv";

					//�A�j���[�V�����C�x���g��񂪓�����CSV�t�@�C���̃p�X��ݒ�B
					std::string animEventCSVFilePath = "Assets/CSV/Monsters/";
					animEventCSVFilePath += monsterName + "/";
					animEventCSVFilePath += monsterName + "_AnimationEvent.csv";

					//�A�j���[�V���������[�h�B
					CMonsterAnimation monsterAnimation;
					monsterAnimation.LoadAnimation(
						monsterName,
						nsUtils::GetWideStringFromString(animCSVFilePath).c_str(),
						nsUtils::GetWideStringFromString(animEventCSVFilePath).c_str()
					);

					//�A�j���[�V�����f�[�^�̃��X�g���擾�A�ݒ�B
					monsterInitData.animDataList = monsterAnimation.GetAnimDataList();

					//�A�j���[�V�����̃t�@�C���p�X�̃��X�g���擾�A�ݒ�B
					monsterInitData.animationFilePath = monsterAnimation.GetAnimFilePathArray();

					//�����X�^�[�f�[�^��ǉ��B
					AddMonsterInitData(monsterInitData);
				}
			}
		}

		CMonster* CMonsterList::CreateMonster(const std::string& monsterName) {

			CMonster* monster = nullptr;
			//�����X�^�[�̃��X�g�����ɎQ�ƁB
			for (const auto& monsterData : m_monsterDataList) {

				//�������O�̃����X�^�[�������B
				if (monsterData.name == monsterName) {

					//�����X�^�[�f�[�^���������B
					SMonsterInitData monsterInitData;
					monsterInitData.name = monsterData.name;
					monsterInitData.animDataList = monsterData.animDataList;
					monsterInitData.animationFilePath = monsterData.animationFilePath;
					monsterInitData.modelFilePath = monsterData.modelFilePath;

					//�����X�^�[�𐶐��B
					monster = NewGO<CMonster>(nsMonster::CMonster::m_kObjName_Monster);
					monster->Create(monsterInitData);
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