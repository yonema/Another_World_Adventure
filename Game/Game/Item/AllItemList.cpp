#include "YonemaEnginePreCompile.h"
#include "AllItemList.h"
#include "../CSV/CSVManager.h"
#include "../Utils/StringManipulation.h"
#include "SelfItem.h"
#include "ThrowItem.h"

#include "../Feature/HealFeature.h"
#include "../Feature/ApplyDamageFeature.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			constexpr const wchar_t* const kItemCSVFilePath = L"Assets/CSV/test.csv";	//アイテム情報が入ったCSVファイルのファイルパス
			constexpr const char* const kItemInfoDelimiter = "*";	//アイテム情報の区切り
		}

		void CAllItemList::LoadAllItemList() {

			//CSV管理クラスを生成。
			nsCSV::CCsvManager csvManager;

			//アイテム情報が入ったcsvファイルをロード。
			csvManager.LoadCSV(kItemCSVFilePath);

			//アイテム情報を生成。
			CreateItemInfo(csvManager.GetCsvData());
		}

		void CAllItemList::CreateItemInfo(std::list<std::vector<std::string>> itemInfo) {

			//アイテムを獲得するために必要な仮情報を初期化。

			SItemInfo itemInfoBase;					//仮のアイテム情報
			std::string title;						//csvから入力される情報のタイトル
			std::vector<std::string> featureInfo;	//仮の効果の配列
			bool addFeature = false;				//効果が追加されたかどうかのフラグ

			//情報を調べる。
			for (const auto& lineData : itemInfo) {

				//さらに詳しい値を調べる。
				for (const auto& detail : lineData) {

					//区切りの合図が入っていたら。
					if (detail == kItemInfoDelimiter) {

						//追加のアイテム情報がないとして、アイテムを追加する。
						m_allItemList.emplace_back(itemInfoBase);

						//仮のアイテム情報を初期化。
						ClearItemInfoBase(itemInfoBase);

						//次へ。
						continue;
					}

					//これから何が入力されてくるのか事前に調べて一時保存。
					if (detail == "NAME" || detail == "TYPE" || detail == "FEATURE") {

						//情報のタイトルを保存。
						title = detail;

						//次へ。
						continue;
					}

					//タイトルがNAMEだったら。
					if (title == "NAME") {

						//名前を設定。
						itemInfoBase.name = detail;

						//次へ。
						continue;
					}

					//タイトルがTYPEだったら。
					if (title == "TYPE") {

						//アイテムのタイプを設定。
						itemInfoBase.itemType = detail;

						//次へ。
						continue;
					}

					//タイトルがFEATUREだったら。
					if (title == "FEATURE") {

						//配列に効果を仮追加。
						featureInfo.emplace_back(detail);

						//追加された。
						addFeature = true;

						//次へ。
						continue;
					}
				}

				//この行で効果が仮追加されていたら。
				if (addFeature) {

					//アイテムに効果を追加。
					itemInfoBase.featureList.emplace_back(featureInfo);

					//仮の配列を初期化。
					featureInfo.clear();

					//フラグを初期化。
					addFeature = false;
				}
			}
		}

		void CAllItemList::ClearItemInfoBase(SItemInfo& itemInfoBase) {

			//仮のアイテム情報を初期化。
			SItemInfo itemInfoBaseInit;
			itemInfoBase = itemInfoBaseInit;
		}

		bool CAllItemList::IsFoundName(std::string itemName) {

			//同じ名前があるかリストから順に検索。
			for (const auto& itemInfo : m_allItemList) {

				//同じ名前のアイテムが見つかった。
				if (itemInfo.name == itemName) {

					//見つかったのでtrue。
					return true;
				}
			}

			//名前がリストに存在していないので警告を出力。
			std::string errorMsg = "検索された名前がリストにありません。 : ";
			errorMsg += itemName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());

			//見つからなかったのでfalse。
			return false;
		}

		const SItemInfo& CAllItemList::GetItemInfo(std::string itemName) {

			//リストから名前を検索する。
			for (const auto& itemInfo : m_allItemList) {

				//同じ名前のアイテムが見つかった。
				if (itemInfo.name == itemName) {

					//このアイテムの情報をリターン。
					return itemInfo;
				}
			}

			//見つからなかった。
			std::string errorMsg = "この名前のアイテムが見つかりませんでした。 : ";
			errorMsg += itemName;

			//警告ウィンドウを出力。
			nsGameWindow::MessageBoxError(nsUtils::GetWideStringFromString(errorMsg).c_str());

			//そもそもここを通ってはいけないが、空の情報をリターン。
			return m_itemList;
		}

		CItem* CItemBuilder::CreateItemBase(std::string itemName) {

			//リストからアイテムを検索し、情報を取得する。
			SItemInfo itemInfo = CAllItemList::GetInstance()->GetItemInfo(itemName);

			//アイテムの雛形を初期化。
			CItem* item = nullptr;

			//タイプがSelfだったら。
			if (itemInfo.itemType == "Self") {

				//自身に付与するタイプのアイテムを生成。
				item = NewGO<CSelfItem>();
			}
			else if (itemInfo.itemType == "Throw") {

				//投げるタイプのアイテムを生成。
				item = NewGO<CThrowItem>();
			}

			//アイテム情報を設定。
			item->SetItemInfo(itemInfo);

			//生成されたアイテムをリターン。
			return item;
		}
	}
}