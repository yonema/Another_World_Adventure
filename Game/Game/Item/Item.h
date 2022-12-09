#pragma once
#include "AllItemList.h"

namespace nsAWA {

	//前方宣言
	class IGameActor;

	namespace nsFeature {

		class CFeature;
	}

	namespace nsItem {

		//アイテムのタイプ
		enum class EnItemType {

			enSelf,			//自身に使用
			enThrow,		//投げる

			enNum,			//種類数
			enNone = -1		//設定なし
		};

		//アイテムクラス
		class CItem : public IGameObject
		{
		public:
			virtual void Use() = 0;

		public:
			void SetItemInfo(const SItemInfo& itemInfo) {

				//アイテム情報を設定。
				m_itemInfo = itemInfo;
			}

			void SetItemName(std::string name) {

				//名前を設定。
				m_itemInfo.name = name;
			}

			std::string GetItemName()const {

				//名前を取得。
				return m_itemInfo.name;
			}

			void SetType(std::string type) {

				//タイプを設定。
				m_itemInfo.itemType = type;
			}
			
			std::string GetType()const {

				//タイプを取得。
				return m_itemInfo.itemType;
			}

			void SetTarget(IGameActor* target) {

				//ターゲットを設定。
				m_target = target;
			}

		protected:
			void CreateFeature();

		private:
			SItemInfo m_itemInfo;	//アイテム情報
			IGameActor* m_target;
		};
	}
}

