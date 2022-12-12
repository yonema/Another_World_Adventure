#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsItem {

		class CItem;
	}

	namespace nsItem {

		//アイテム情報
		struct SItemInfo {

			std::string name = "";								//名前
			std::string itemType = "";							//アイテムのタイプ
			std::list<std::vector<std::string>> featureList;	//効果の情報のリスト
		};

		//ゲーム内でのあらゆるアイテムのリスト
		class CAllItemList : nsUtils::SNoncopyable
		{
		public:
			static CAllItemList* GetInstance() {

				//インスタンスをリターン。
				static CAllItemList* instance = new CAllItemList;

				return instance;
			}

			static void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadAllItemList();

			bool IsFoundName(std::string itemName);

		public:
			const SItemInfo& GetItemInfo(std::string itemName);

		private:
			void CreateItemInfo(std::list<std::vector<std::string>> itemInfo);

			void ClearItemInfoBase(SItemInfo& itemInfoBase);

		private:
			std::list<SItemInfo> m_allItemList;		//全てのアイテムの情報
			SItemInfo m_itemList;					//空のアイテム情報
		};

		//アイテム生成クラス
		class CItemBuilder : nsUtils::SNoncopyable {

		public:
			CItem* CreateItemBase(std::string itemName);
		};
	}
}