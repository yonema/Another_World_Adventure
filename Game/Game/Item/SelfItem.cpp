#include "YonemaEnginePreCompile.h"
#include "SelfItem.h"

namespace nsAWA {

	namespace nsItem {

		void CSelfItem::Use() {
			
			//効果を発動。
			CreateFeature();

			//自身を破棄。
			DeleteGO(this);
		}
	}
}