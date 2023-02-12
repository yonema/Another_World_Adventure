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

			void SetTatget(IGameActor* target) {

				//ターゲットを設定。
				m_target = target;
			}

			const std::list<SHasItem>& GetItemList()const {

				//アイテムリストを取得。
				return m_sItemList;
			}

			void Init(IGameActor* target) {

				//ターゲットを設定。
				m_target = target;
			}

			void NextItem() {

				//先頭データを取得。
				auto frontDataItr = m_sItemList.begin();
				std::string frontDataName = (*frontDataItr).name;
				int frontDataNum = (*frontDataItr).hasNum;

				//先頭データを破棄。
				m_sItemList.erase(frontDataItr);

				//最終にデータを追加。
				AddItem(frontDataName, frontDataNum, true);
			}

			void BackItem() {

				//最終データを取得。
				auto backDataItr = m_sItemList.end();
				backDataItr--;
				std::string backDataName = (*backDataItr).name;
				int backDataNum = (*backDataItr).hasNum;

				//最終データを破棄。
				m_sItemList.erase(backDataItr);

				//先頭にデータを追加。
				AddItem(backDataName, backDataNum, false);
			}

			void UseItem();

#ifdef _DEBUG

			const std::string& GetItemName() {

				//先頭のアイテムの名前を取得。
				return ((*m_sItemList.begin()).name);
			}

			int GetItemNum() {

				//先頭のアイテムの数を取得。
				return ((*m_sItemList.begin()).hasNum);
			}

			void GetAllItemName(std::list<std::string> nameVec)
			{
				// 先頭から最後までのアイテムの名前を取得
				for (auto forNum : m_sItemList) {
					nameVec.push_back(forNum.name);
				}
			}

#endif // _DEBUG


			void AddItem(std::string itemName, int getNum = 1, bool back = true);

			bool HasItem()const {

				//サイズが0より大きいかどうかをリターン。
				return m_sItemList.size() > 0;
			}

		private:
			std::list<SHasItem> m_sItemList;	//アイテムリスト
			IGameActor* m_target = nullptr;		//ターゲット
		};
	}
}