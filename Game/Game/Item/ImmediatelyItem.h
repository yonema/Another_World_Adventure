#pragma once
#include "Item.h"

namespace nsAWA {

	namespace nsItem {

		//�����ɔ�������A�C�e���N���X
		class CImmediatelyItem : public CItem
		{
			void Use()override final;
		};
	}
}

