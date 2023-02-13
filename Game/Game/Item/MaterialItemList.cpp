#include "YonemaEnginePreCompile.h"
#include "MaterialItemList.h"
#include "../CSV/CSVManager.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const wchar_t* kMaterialItemListCSVFilePath = L"Assets/CSV/MaterialItemList.csv";
		}

		void CMaterialItemList::LoadMaterialItemList() {

			//素材アイテムリストのCSVをロード。
			nsCSV::CCsvManager csvManager;
			csvManager.LoadCSV(kMaterialItemListCSVFilePath);

			SMaterialItemInfo materialItemInfoBase;	//仮の素材アイテム情報
			

			//情報を調べる。
			for (const auto& lineData : csvManager.GetCsvData()) {

				//見出しを取得。
				std::string title = lineData[0];

				//区切りの合図が入っていたら。
				if (title == "*") {

					//追加のアイテム情報がないとして、アイテムを追加する。
					m_materialItemList.emplace_back(materialItemInfoBase);

					//仮のアイテム情報を初期化。
					SMaterialItemInfo itemInfoBaseInit;
					materialItemInfoBase = itemInfoBaseInit;

					//次へ。
					continue;
				}

				//タイトルがNAMEだったら。
				if (title == "NAME") {

					//名前を設定。
					materialItemInfoBase.name = lineData[1];

					//次へ。
					continue;
				}

				//タイトルがRANKだったら。
				if (title == "RANK") {

					//アイテムのタイプを設定。
					materialItemInfoBase.rank = lineData[1];

					//次へ。
					continue;
				}
			}
		}

		const SMaterialItemInfo& CMaterialItemList::GetMaterialItemInfo(const std::string& itemName) {

			//リストから名前を検索する。
			for (const auto& materialItemInfo : m_materialItemList) {

				//同じ名前のアイテムが見つかった。
				if (materialItemInfo.name == itemName) {

					//このアイテムの情報をリターン。
					return materialItemInfo;
				}
			}

			//見つからなかった。
			std::string errorMsg = "この名前の素材アイテムが見つかりませんでした。 : ";
			errorMsg += itemName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());
			std::abort();
		}

		bool CMaterialItemList::IsFoundName(std::string itemName) {

			//同じ名前があるかリストから順に検索。
			for (const auto& materialItem : m_materialItemList) {

				//同じ名前の素材アイテムが見つかった。
				if (materialItem.name == itemName) {

					//見つかったのでtrue。
					return true;
				}
			}

			//名前がリストに存在していないので警告を出力。
			std::string errorMsg = "CMaterialItemList : 検索された素材アイテムがリストにありません。 : ";
			errorMsg += itemName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());

			//見つからなかったのでfalse。
			return false;
		}
	}
}