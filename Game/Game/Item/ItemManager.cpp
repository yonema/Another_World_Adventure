#include "YonemaEnginePreCompile.h"
#include "ItemManager.h"
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		void CItemManager::UseItem() {

			//アイテムのリストが空なら。
			if (!HasItem()) {

				//アイテム使用ができないのでリターン。
				return;
			}

			//使いたいアイテムのイテレータを取り出す。
			auto itr = m_itemList.begin();
			itr += m_selectItemNum;

			//アイテムを使用。
			(*itr)->Use();

			//使ったアイテムを破棄。
			DeleteGO(*itr);

			//リストからアイテムを削除。
			m_itemList.erase(itr);
		}
	}
}