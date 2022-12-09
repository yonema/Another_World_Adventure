#include "YonemaEnginePreCompile.h"
#include "SelfItem.h"

namespace nsAWA {

	namespace nsItem {

		void CSelfItem::Use() {
			
			//Œø‰Ê‚ğ”­“®B
			CreateFeature();

			//©g‚ğ”jŠüB
			DeleteGO(this);
		}
	}
}