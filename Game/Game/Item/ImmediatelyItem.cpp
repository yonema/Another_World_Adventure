#include "YonemaEnginePreCompile.h"
#include "ImmediatelyItem.h"

namespace nsAWA {

	namespace nsItem {

		void CImmediatelyItem::Use() {
			
			//効果を発動。
			ExecuteFeature();
		}
	}
}