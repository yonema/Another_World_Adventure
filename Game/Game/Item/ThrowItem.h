#pragma once
#include "Item.h"
#include "ItemCollision.h"

namespace nsAWA {

	namespace nsItem {

		//投げるアイテムクラス
		class CThrowItem : public CItem
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void Use()override final;

		private:
			void InitItemModel();

		public:
			void SetStartPosition(const CVector3& startPosition) {

				//投げ開始の座標を格納。
				m_startPosition = &startPosition;
			}

			void SetThrowDirection(const CVector3& throwDirection) {

				//投げる方向を格納。
				m_throwDirection = &throwDirection;
			}

		private:
			CModelRenderer* m_itemModel = nullptr;		//モデル
			CItemCollision m_collision;					//当たり判定
			const CVector3* m_startPosition = nullptr;	//投げる位置
			const CVector3* m_throwDirection = nullptr;	//投げる方向
		};
	}
}

