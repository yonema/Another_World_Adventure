#include "YonemaEnginePreCompile.h"
#include "SelfItem.h"

namespace nsAWA {

	namespace nsItem {

		void CSelfItem::Use() {
			
			//���ʂ𔭓��B
			CreateFeature();

			//���g��j���B
			DeleteGO(this);
		}
	}
}