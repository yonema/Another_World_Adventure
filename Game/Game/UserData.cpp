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

		//データを保存。
		csvManager.SaveCSV(kUserDataCSVFilePath, m_userData);
	}

	void CUserData::Load() {

		//データ情報を破棄。
		m_userData.clear();

		//プレイヤーを検索。
		auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//ユーザーデータ格納用のCSVをロード。
		nsCSV::CCsvManager csvManager;
		csvManager.LoadCSV(kUserDataCSVFilePath);

		//データのイテレータを取得。
		auto data = csvManager.GetCsvData();
		auto itr = data.begin();

		//ステータスをロード。
		player->GetStatus()->LoadStatus(*itr);
		itr++;

		//使用可能なアクティブスキルのリストをロード。
		for (const auto& data : *itr) {

			nsPlayer::CPlayerManager::GetInstance()->AddCanUseActiveSkill(data);
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

		//使用可能なアクティブスキルのリストを保存する。
		std::vector<std::string> canUseActiveSkillData;

		for (const auto& activeSkill : nsPlayer::CPlayerManager::GetInstance()->GetCanUseActiveSkillList()) {

			//スキル名をリストに追加。
			canUseActiveSkillData.emplace_back(activeSkill.name);
		}

		//ユーザーデータに追加。
		m_userData.emplace_back(canUseActiveSkillData);
	}
}