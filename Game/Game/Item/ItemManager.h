#pragma once

namespace nsAWA {

	//エイリアス宣言
	namespace nsItem {

		class CItem;
	}

	namespace nsItem {

		//アイテム管理クラス
		class CItemManager : nsUtils::SNoncopyable
		{
		public:
			void AddItem(nsItem::CItem* item) {

				//アイテムリストにアイテムを追加。
				m_itemList.emplace_back(item);
			}

			void UseItem();

			void AddSelectItemNum() {

				//リストが空なら。
				if (!HasItem()) {

					//終了。
					return;
				}

				//次のアイテムを見る。
				m_selectItemNum++;

				//アイテムのリストのサイズ以上なら。
				if (m_selectItemNum >= m_itemList.size()) {

					//最初のアイテムを見る。
					m_selectItemNum = 0;
				}
			}

			void SubSelectItemNum() {

				//リストが空なら。
				if (!HasItem()) {

					//終了。
					return;
				}

				//前のアイテムを見る。
				m_selectItemNum--;

				//マイナス値になっていたら。
				if (m_selectItemNum < 0) {

					//最後のアイテムを見る。
					m_selectItemNum = m_itemList.size() - 1;
				}
			}

			bool HasItem()const {

				//アイテムを持っているかどうかを返す。
				return m_itemList.size() != 0;
			}

		private:
			int m_selectItemNum = 0;			//選択中のアイテム番号
			std::vector<CItem*> m_itemList;		//アイテムリスト
		};
	}
}