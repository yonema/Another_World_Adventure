#pragma once

namespace nsAWA {

	//前方宣言
	class IGameActor;
	namespace nsItem {

		class CItem;
	}

	namespace nsItem {

		//アイテム管理クラス
		class CItemManager : nsUtils::SNoncopyable
		{
		private:
			//手持ちのアイテム情報
			struct SHasItem {

				std::string name = "";	//名前
				int hasNum = 0;			//所持数
			};
		public:

			void Init(IGameActor* target) {

				//ターゲットを設定。
				m_target = target;
			}

			void UseItem();

			void AddItem(std::string itemName, int getNum = 1);

			bool HasItem()const {

				//サイズが0より大きいかどうかをリターン。
				return m_sItemList.size() > 0;
			}

		private:
			int m_selectItemNum = 0;			//選択中のアイテム番号
			std::list<SHasItem> m_sItemList;	//アイテムリスト
			IGameActor* m_target = nullptr;		//ターゲット
		};
	}
}