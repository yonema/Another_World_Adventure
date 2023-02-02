#include "YonemaEnginePreCompile.h"
#include "UserData.h"
#include "CSV/CSVManager.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"


namespace nsAWA {

	namespace {

		constexpr const wchar_t* kUserDataCSVFilePath = L"Assets/CSV/UserData.csv";		//ユーザーデータのCSVファイルパス
	}

	void CUserData::Save() {

		//データ情報を破棄。
		m_userData.clear();

		//プレイヤーを検索。
		auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//ユーザーデータ格納用のCSVをロード。
		nsCSV::CCsvManager csvManager;
		csvManager.LoadCSV(kUserDataCSVFilePath);

		//スタータスを保存。
		SaveStatus(player);

		//使用可能なアクティブスキルのリストを保存。
		SaveCanUseActiveSkillList(player);

		//アイテムを保存。
		SaveItem();

		//データを保存。
		csvManager.SaveCSV(kUserDataCSVFilePath, m_userData);
	}

	void CUserData::Load() {

		//データ情報を破棄。
		m_userData.clear();

		//プレイヤーを検索。
		auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		if (!player) {

			nsGameWindow::MessageBoxError(L"UserData : プレイヤーが見つかりませんでした。");
		}

		//ユーザーデータ格納用のCSVをロード。
		nsCSV::CCsvManager csvManager;
		csvManager.LoadCSV(kUserDataCSVFilePath);

		//データのイテレータを取得。
		auto data = csvManager.GetCsvData();
		auto itr = data.begin();

		//ステータスをロード。
		player->GetStatus()->LoadStatus(*itr);
		itr++;

		//プレイヤー管理クラスを取得。
		auto playerManager = nsPlayer::CPlayerManager::GetInstance();
		playerManager->SetPlayer(player);

		//使用可能なアクティブスキルのリストをロード。
		for (const auto& data : *itr) {

			playerManager->AddCanUseActiveSkill(data);
		}
		itr++;

		//アイテムのリストをロード。
		auto playerItemManager = playerManager->GetItemManager();

		
		for (int dataNum = 0; dataNum < (*itr).size(); dataNum++) {

			std::string name = (*itr)[dataNum];
			int num = std::stoi((*itr)[++dataNum]);

			playerItemManager->AddItem(name, num, true);
		}
	}

	void CUserData::SaveStatus(nsPlayer::CPlayer* player) {

		//ステータスをリストに格納。
		std::vector<std::string> statusData;
		statusData.emplace_back(std::to_string(player->GetStatus()->GetLevel()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetHP()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetMaxHP()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetMP()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetMaxMP()));

		//ユーザーデータに追加。
		m_userData.emplace_back(statusData);
	}

	void CUserData::SaveCanUseActiveSkillList(nsPlayer::CPlayer* player) {

		//プレイヤーを検索。
		if (!nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {

			return;
		}

		//使用可能なアクティブスキルのリストを保存する。
		std::vector<std::string> canUseActiveSkillData;
		
		for (const auto& activeSkill : nsPlayer::CPlayerManager::GetInstance()->GetCanUseActiveSkillListAll()) {

			//スキル名をリストに追加。
			canUseActiveSkillData.emplace_back(activeSkill.name);
		}

		//ユーザーデータに追加。
		m_userData.emplace_back(canUseActiveSkillData);
	}

	void CUserData::SaveItem() {

		//プレイヤーを検索。
		if (!nsPlayer::CPlayerManager::GetInstance()->FindPlayer()) {

			return;
		}

		//アイテムのリストを保存する。
		std::vector<std::string> itemData;

		//アイテム管理クラスを取得。
		auto itemManager = nsPlayer::CPlayerManager::GetInstance()->GetItemManager();

		//アイテムを順に参照。
		for (const auto& item : itemManager->GetItemList()) {

			//アイテム情報を格納。
			itemData.emplace_back(item.name);
			itemData.emplace_back(std::to_string(item.hasNum));
		}

		//ユーザーデータに追加。
		m_userData.emplace_back(itemData);
	}
}