#include "YonemaEnginePreCompile.h"
#include "UserData.h"
#include "CSV/CSVManager.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Armor/Armor.h"
#include "Skill/PassiveSkillManager.h"
#include "Skill/PassiveSkill.h"


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

		//武器と防具を保存。
		SaveWeaponAndArmor(player);

		//セット中のアクティブスキルを保存。
		SaveSetActiveSkill(player);

		//セット中のパッシブスキルを保存。
		SaveSetPassiveSkill(player);

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

		//アイテムを追加。
		for (int dataNum = 0; dataNum < (*itr).size(); dataNum++) {

			std::string name = (*itr)[dataNum];
			int num = std::stoi((*itr)[++dataNum]);

			playerItemManager->AddItem(name, num, true);
		}
		itr++;

		//武器と防具をロード。
		playerManager->SetWeapon((*itr)[0]);
		playerManager->SetArmor((*itr)[1]);
		itr++;

		//アクティブスキルをロード。
		for (int dataNum = 0; dataNum < (*itr).size(); dataNum++) {

			//名前を取得。
			std::string name = (*itr)[dataNum];

			//Noneじゃなければ。
			if (name != "None") {

				//アクティブスキルを設定。
				playerManager->SetActiveSkill(dataNum, name);
			}
		}
		itr++;
		
		//パッシブスキルの装着可能数を設定。
		playerManager->SetActiveSkillMaxNum(static_cast<int>((*itr).size()));

		//パッシブスキルをロード。
		for (int dataNum = 0; dataNum < (*itr).size(); dataNum++) {

			//名前を取得。
			std::string name = (*itr)[dataNum];

			//Noneじゃなければ。
			if (name != "None") {

				//パッシブスキルを設定。
				playerManager->SetPassiveSkill(dataNum, name);
			}
		}
	}

	void CUserData::SaveStatus(nsPlayer::CPlayer* player) {

		//ステータスをリストに格納。
		std::vector<std::string> statusData;
		statusData.emplace_back(player->GetStatus()->GetPlayerName());
		statusData.emplace_back(std::to_string(player->GetStatus()->GetLevel()));
		statusData.emplace_back(std::to_string(player->GetStatus()->GetExp()));
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

	void CUserData::SaveWeaponAndArmor(nsPlayer::CPlayer* player) {

		//装備中の武器と防具の名前を取得。
		std::string playerWeaponName = player->GetWeapon()->GetWeaponName();
		std::string playerArmorName = player->GetArmor()->GetArmorName();

		std::vector<std::string> weaponAndArmorName;

		//名前をリストに追加。
		weaponAndArmorName.emplace_back(playerWeaponName);
		weaponAndArmorName.emplace_back(playerArmorName);

		//ユーザーデータに追加。
		m_userData.emplace_back(weaponAndArmorName);
	}

	void CUserData::SaveSetActiveSkill(nsPlayer::CPlayer* player) {

		std::vector<std::string> setActiveSkillName;

		//アクティブスキルの名前をデータに保存。
		for (int skillNum = 0; skillNum < static_cast<int>(nsPlayer::EnActiveSkillListNumber::enActiveSkill_Num); skillNum++) {

			std::string skillName = nsPlayer::CPlayerManager::GetInstance()->GetActiveSkillName(skillNum);

			//もしアクティブスキルがセットされていなければ。
			if (skillName == nsPlayer::CPlayerManager::m_kTestFontNotFound) {

				//Noneを保存。
				setActiveSkillName.emplace_back("None");
			}
			else {

				//スキル名を保存。
				setActiveSkillName.emplace_back(skillName);
			}
		}

		//ユーザーデータに追加。
		m_userData.emplace_back(setActiveSkillName);
	}

	void CUserData::SaveSetPassiveSkill(nsPlayer::CPlayer* player) {

		std::vector<std::string> setPassiveSkillName;

		auto* passiveSkillManager = player->GetPassiveSkillManager();

		//パッシブスキルの名前をデータに保存。

		//パッシブスキルを順に参照。
		for (const auto& passiveSkill : passiveSkillManager->GetPassiveSkillList()) {

			std::string passiveSkillName = "None";

			//設定されていれば。
			if (passiveSkill != nullptr) {

				//名前を取得。
				passiveSkillName = passiveSkill->GetName();
			}

			//データに追加。
			setPassiveSkillName.emplace_back(passiveSkillName);
		}

		//ユーザーデータに追加。
		m_userData.emplace_back(setPassiveSkillName);
	}
}