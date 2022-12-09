#pragma once
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		//即座に発動するアイテムクラス
		class CSelfItem : public CItem
		{
			void Use()override final;
		};
	}
}

