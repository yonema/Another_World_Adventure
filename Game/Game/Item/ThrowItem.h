#pragma once
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		//投げるアイテムクラス
		class CThrowItem : public CItem
		{
		public:
			void Use()override final;
		};
	}
}

