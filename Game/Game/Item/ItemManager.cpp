#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "ItemManager.h"
#include "AllItemList.h"
#include "SelfItem.h"
#include "ThrowItem.h"

namespace nsAWA {

	namespace nsItem {

		namespace {

			const CVector3 kThrowAddPosition = { 0.0f,100.0f,0.0f };	//投げる位置の修正加算座標
		}

		void CItemManager::UseItem() {

			//アイテムのリストが空なら。
			if (!HasItem()) {
			
				//アイテム使用ができないのでリターン。
				return;
			}
			
			//使いたいアイテムのイテレータを取り出す。
			auto itr = m_sItemList.begin();
			
			//アイテムを生成。
			CItemBuilder itemBuilder;
			CItem* item = itemBuilder.CreateItemBase((*itr).name);

			//アイテムのクラス名を取得。
			const type_info& id = typeid(*item);

			//自身に使うアイテムだったら。
			if (typeid(nsItem::CSelfItem) == id) {

				//ターゲットを自身に設定。
				dynamic_cast<nsItem::CSelfItem*>(item)->SetTarget(m_target);
			}
			//投げるアイテムだったら。
			else if (typeid(nsItem::CThrowItem) == id) {

				//投げ開始位置と投げる方向を設定。
				dynamic_cast<nsItem::CThrowItem*>(item)->SetStartPosition(m_target->GetPosition());
				dynamic_cast<nsItem::CThrowItem*>(item)->SetThrowDirection(m_target->GetForwardDirection());
			}

			//アイテムを使用。
			item->Use();

			//１つ消費する。
			(*itr).hasNum--;

			//このアイテムの所持数が0個になったら。
			if ((*itr).hasNum == 0) {

				//リストから削除。
				m_sItemList.erase(itr);
			}
		}

		void CItemManager::AddItem(std::string itemName, int getNum, bool back) {

			//リストに名前があるか検索。
			bool isFound = CAllItemList::GetInstance()->IsFoundName(itemName);

			//リストになかった。
			if (!isFound) {

				//終了。
				return;
			}

			//手持ちのアイテムを順に参照。
			for (auto& itemList : m_sItemList) {

				//名前が一致したら。
				if (itemList.name == itemName) {

					//既に同じアイテムを持っているので所持数を加算。
					itemList.hasNum += getNum;

					//終了。
					return;
				}
			}

			//持っていなかったのでアイテム情報を生成。
			SHasItem item;
			item.name = itemName;	//名前
			item.hasNum = getNum;	//所持数


			if (back) {
				//新たにアイテム情報を追加。
				m_sItemList.emplace_back(item);
			}
			else {
				//新たにアイテム情報を追加。
				m_sItemList.emplace_front(item);
			}
		}
	}
}