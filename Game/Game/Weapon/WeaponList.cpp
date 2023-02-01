#include "YonemaEnginePreCompile.h"
#include "WeaponList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsWeapon {

		namespace {

			constexpr const wchar_t* kWeaponCSVFilePath = L"Assets/CSV/Player/PlayerWeapon.csv";	//武器のリストのCSVのファイルパス
		}

		void CWeaponList::LoadWeaponList() {

			//武器のリストをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kWeaponCSVFilePath);

			SWeaponInfo weaponInfo;

			//武器のデータを順に取得。
			for (const auto& lineData : csvManager.GetCsvData()) {

				//見出しを取得。
				std::string title = lineData[0];

				//区切りなら。
				if (title == "*") {

					//データをリストに追加。
					m_weaponDataList.emplace_back(weaponInfo);

					//データを初期化。
					SWeaponInfo clearInfo;
					weaponInfo = clearInfo;

					//次へ。
					continue;
				}

				if (title == "NAME") {

					std::string name = lineData[1];

					//名前を設定。
					weaponInfo.name = name;

					//モデルのファイルパスを設定。
					weaponInfo.modelFilePath = "Assets/Models/Weapons/";
					weaponInfo.modelFilePath += name;
					weaponInfo.modelFilePath += ".fbx";
				}
				else if (title == "TYPE") {

					std::string type = lineData[1];

					if (type == "Sword") {

						weaponInfo.weaponType = EnWeaponType::enSword;
					}
					else if (type == "Axe") {

						weaponInfo.weaponType = EnWeaponType::enAxe;
					}
					else if (type == "Wand") {

						weaponInfo.weaponType = EnWeaponType::enWand;
					}
					else {

						//名前がリストに存在していないので警告を出力。
						std::string errorMsg = "CWeaponList : タイプの設定が不適切です。";
						errorMsg += type;

						//警告ウィンドウを出力。
						nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
						std::abort();
					}
				}
				else if (title == "ATK") {

					//物理攻撃力を設定。
					weaponInfo.attack = std::stof(lineData[1]);
				}
				else if (title == "INT") {

					//魔法攻撃力を設定。
					weaponInfo.intelligence = std::stof(lineData[1]);
				}
				else if (title == "CRI") {

					//クリティカル率を設定。
					weaponInfo.critical = std::stof(lineData[1]);
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

		const SWeaponInfo& CWeaponList::GetWeaponData(const std::string& weaponName) {

			//武器のリストを順に参照。
			for (const auto& weaponData : m_weaponDataList) {

				//同じ名前の武器が見つかったら。
				if (weaponData.name == weaponName) {

					//そのデータをリターン。
					return weaponData;
				}
			}

			//名前がリストに存在していないので警告を出力。
			std::string errorMsg = "CWeaponList : 検索された名前がリストにありません。 : ";
			errorMsg += weaponName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}
	}
}