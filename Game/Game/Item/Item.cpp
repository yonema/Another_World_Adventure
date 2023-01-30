#include "YonemaEnginePreCompile.h"
#include "Item.h"
#include "../Feature/Feature.h"
#include "../Feature/FeatureBuilder.h"

namespace nsAWA {

	namespace nsItem {

		void CItem::CreateFeature() {

			//効果生成クラスを生成。
			nsFeature::CFeatureBuilder featureBuilder;

			//効果を生成。
			featureBuilder.CreateFeature(nullptr, m_target, m_itemInfo.featureList);
		}
	}
}