#pragma once
namespace nsAWA {

	namespace nsItem {

		//素材アイテム情報
		struct SMaterialItemInfo {

			std::string name = "NoName";	//名前
			std::string rank = "NoRank";	//レア度
		};

		//素材アイテムリスト
		class CMaterialItemList : nsUtils::SNoncopyable
		{
		public:
			static CMaterialItemList* GetInstance() {

				//インスタンスを生成。
				static CMaterialItemList* instance = new CMaterialItemList;

				//インスタンスをリターン。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}
			const SMaterialItemInfo& GetMaterialItemInfo(const std::string& itemName);

			void LoadMaterialItemList();

			bool IsFoundName(std::string itemName);

		private:
			std::list<SMaterialItemInfo> m_materialItemList;	//素材アイテムリスト
		};
	}
}

