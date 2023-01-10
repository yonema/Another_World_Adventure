#include "YonemaEnginePreCompile.h"
#include "Item.h"
#include "../Feature/Feature.h"
#include "../Feature/FeatureBuilder.h"

namespace nsAWA {

	namespace nsItem {

		void CItem::CreateFeature() {

			//���ʐ����N���X�𐶐��B
			nsFeature::CFeatureBuilder featureBuilder;

			//���ʂ𐶐��B
			featureBuilder.CreateFeature(nullptr, m_target, m_itemInfo.featureList);
		}
	}
}