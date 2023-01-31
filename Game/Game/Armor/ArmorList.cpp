#include "YonemaEnginePreCompile.h"
#include "ArmorList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsArmor {

		namespace {

			constexpr const wchar_t* kArmorCSVFilePath = L"Assets/CSV/Player/PlayerArmor.csv";	//防具のリストのCSVのファイルパス
		}

		void CArmorList::LoadArmorList() {

			//防具のリストをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kArmorCSVFilePath);

			SArmorInfo armorInfo;

			//防具のデータを順に取得。
			for (const auto& lineData : csvManager.GetCsvData()) {

				//見出しを取得。
				std::string title = lineData[0];

				//区切りなら。
				if (title == "*") {

					//データをリストに追加。
					m_armorDataList.emplace_back(armorInfo);

					//データを初期化。
					SArmorInfo clearInfo;
					armorInfo = clearInfo;

					//次へ。
					continue;
				}

				if (title == "NAME") {

					std::string name = lineData[1];

					//名前を設定。
					armorInfo.name = name;
				}
				else if (title == "DEF") {

					//物理防御力を設定。
					armorInfo.defence = std::stof(lineData[1]);
				}
				else if (title == "MND") {

					//魔法防御力を設定。
					armorInfo.mind = std::stof(lineData[1]);
				}
				else {

					//名前がリストに存在していないので警告を出力。
					std::string errorMsg = "CWeaponList : 見出しデータが不適切です。";
					errorMsg += title;

					//警告ウィンドウを出力。
					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
					std::abort();
				}
			}
		}

		const SArmorInfo& CArmorList::GetArmorData(const std::string& armorName) {

			//防具のリストを順に参照。
			for (const auto& armorData : m_armorDataList) {

				//同じ名前の防具が見つかったら。
				if (armorData.name == armorName) {

					//そのデータをリターン。
					return armorData;
				}
			}

			//名前がリストに存在していないので警告を出力。
			std::string errorMsg = "CArmorList : 検索された名前がリストにありません。 : ";
			errorMsg += armorName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}
	}
}