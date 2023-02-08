#include "YonemaEnginePreCompile.h"
#include "PassiveSkillList.h"
#include "PassiveSkill.h"
#include "../CSV/CSVManager.h"
#include "../Feature/FeatureBuilder.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr const wchar_t* kPassiveSkillCSVFilePath = L"Assets/CSV/Player/PassiveSkillList.csv";	//パッシブスキルのCSVファイルパス
		}

		void CPassiveSkillList::LoadPassiveSkillList() {

			//パッシブスキルのリストのCSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kPassiveSkillCSVFilePath);
			auto passiveSkillData = csvManager.GetCsvData();

			SPassiveSkillData passiveSkillDataBase;

			//アクティブスキルのデータを順に参照。
			for (auto& lineData : passiveSkillData) {

				//見出しを取得。
				std::string title = lineData[0];

				//区切りなら。
				if (title == "*") {

					//パッシブスキルの情報をリストに追加。
					m_passiveSkillList.emplace_back(passiveSkillDataBase);

					//データを初期化。
					SPassiveSkillData clearData;
					passiveSkillDataBase = clearData;

					//次へ。
					continue;
				}
				else if (title == "NAME") {

					//名前を取得。
					std::string name = lineData[1];
					passiveSkillDataBase.name = name;

				}
				else if (title == "FEATURE") {

					//効果のリストを取得。
					lineData.erase(lineData.begin());
					passiveSkillDataBase.featureList.emplace_back(lineData);
				}
				else {

					//エラー出力。
					std::string errorMsg = "CPassiveSkill : CSVデータのタイトル情報が不適切です。 : ";
					errorMsg += title;
					nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

					std::abort();
				}
			}
		}

		const SPassiveSkillData& CPassiveSkillList::GetPassiveSkillData(const std::string& passiveSkillName) {

			//パッシブスキルのリストを順に参照。
			for (const auto& passiveSkillData : m_passiveSkillList) {

				//同じ名前のパッシブスキルが見つかったら。
				if (passiveSkillData.name == passiveSkillName) {

					//そのデータをリターン。
					return passiveSkillData;
				}
			}

			//名前がリストに存在していないので警告を出力。
			std::string errorMsg = "検索された名前がリストにありません。 : ";
			errorMsg += passiveSkillName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();

		}

		CPassiveSkill* CPassiveSkillBuilder::CreatePassiveSkill(const std::string& passiveSkillName) {

			//名前からアクティブスキルのデータを取得。
			SPassiveSkillData passiveSkillData = CPassiveSkillList::GetInstance()->GetPassiveSkillData(passiveSkillName);

			//パッシブスキルを生成。
			CPassiveSkill* passiveSkill = new CPassiveSkill;

			//各種設定。
			passiveSkill->SetName(passiveSkillData.name);
			passiveSkill->SetFeatureListStr(passiveSkillData.featureList);

			//生成したパッシブスキルをリターン。
			return passiveSkill;
		}
	}
}