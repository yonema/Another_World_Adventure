#include "YonemaEnginePreCompile.h"
#include "UserData.h"
#include "CSV/CSVManager.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"


namespace nsAWA {

	namespace {

		constexpr const wchar_t* kUserDataCSVFilePath = L"Assets/CSV/UserData.csv";		//���[�U�[�f�[�^��CSV�t�@�C���p�X
	}

	void CUserData::Save() {

		//�f�[�^����j���B
		m_userData.clear();

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//���[�U�[�f�[�^�i�[�p��CSV�����[�h�B
		nsCSV::CCsvManager csvManager;
		csvManager.LoadCSV(kUserDataCSVFilePath);

		//�X�^�[�^�X��ۑ��B
		SaveStatus(player);

		//�g�p�\�ȃA�N�e�B�u�X�L���̃��X�g��ۑ��B
		SaveCanUseActiveSkillList(player);

		//�A�C�e����ۑ��B
		SaveItem();

		//�f�[�^��ۑ��B
		csvManager.SaveCSV(kUserDataCSVFilePath, m_userData);
	}

	void CUserData::Load() {

		//�f�[�^����j���B
		m_userData.clear();

		//�v���C���[�������B
		auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		if (!player) {

			nsGameWindow::MessageBoxError(L"UserData : �v���C���[��������܂���ł����B");
		}

		//���[�U�[�f�[�^�i�[�p��CSV�����[�h�B
		nsCSV::CCsvManager csvManager;
		csvManager.LoadCSV(kUserDataCSVFilePath);

		//�f�[�^�̃C�e���[�^���擾�B
		auto data = csvManager.GetCsvData();
		auto itr = data.begin();

		//�X�e�[�^�X�����[�h�B
		player->GetStatus()->LoadStatus(*itr);
		itr++;

		//�v���C���[�Ǘ��N���X���擾�B
		auto playerManager = nsPlayer::CPlayerManager::GetInstance();
		playerManager->SetPlayer(player);

		//�g�p�\�ȃA�N�e�B�u�X�L���̃��X�g�����[�h�B
		for (const auto& data : *itr) {

			playerManager->AddCanUseActiveSkill(data);
		}
		itr++;

		//�A�C�e���̃��X�g�����[�h�B
		auto playerItemManager = playerManager->GetItemManager();

		
		for (int dataNum = 0; dataNum < (*itr).size(); dataNum++) {

			std::string name = (*itr)[dataNum];
			int num = std::stoi((*itr)[++dataNum]);

			playerItemManager->AddItem(name, num, true);
		}
	}

	void CUserData::SaveStatus(nsPlayer::CPlayer* player) {

		//�X�e�[�^�X�����X�g�Ɋi�[�B
		std::vector<std::string> statusData;
		statusData.emplace_back(std::to_string(player->GetStatus()->GetLevel()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetHP()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetMaxHP()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetMP()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetMaxMP()));

		//���[�U�[�f�[�^�ɒǉ��B
		m_userData.emplace_back(statusData);
	}

	void CUserData::SaveCanUseActiveSkillList(nsPlayer::CPlayer* player) {

		//�v���C���[�������B
		if (!nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {

			return;
		}

		//�g�p�\�ȃA�N�e�B�u�X�L���̃��X�g��ۑ�����B
		std::vector<std::string> canUseActiveSkillData;
		
		for (const auto& activeSkill : nsPlayer::CPlayerManager::GetInstance()->GetCanUseActiveSkillListAll()) {

			//�X�L���������X�g�ɒǉ��B
			canUseActiveSkillData.emplace_back(activeSkill.name);
		}

		//���[�U�[�f�[�^�ɒǉ��B
		m_userData.emplace_back(canUseActiveSkillData);
	}

	void CUserData::SaveItem() {

		//�v���C���[�������B
		if (!nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {

			return;
		}

		//�A�C�e���̃��X�g��ۑ�����B
		std::vector<std::string> itemData;

		//�A�C�e���Ǘ��N���X���擾�B
		auto itemManager = nsPlayer::CPlayerManager::GetInstance()->GetItemManager();

		//�A�C�e�������ɎQ�ƁB
		for (const auto& item : itemManager->GetItemList()) {

			//�A�C�e�������i�[�B
			itemData.emplace_back(item.name);
			itemData.emplace_back(std::to_string(item.hasNum));
		}

		//���[�U�[�f�[�^�ɒǉ��B
		m_userData.emplace_back(itemData);
	}
}