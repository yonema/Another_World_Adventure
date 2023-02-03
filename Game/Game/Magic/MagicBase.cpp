#include "YonemaEnginePreCompile.h"
#include "MagicBase.h"
#include "../Feature/FeatureBuilder.h"

namespace nsAWA {

	namespace nsMagic {

		void CMagicBase::ExecuteFeature(IGameActor* target) {

			//���ʂ𐶐��B
			nsFeature::CFeatureBuilder featureBuilder;
			featureBuilder.CreateFeature(m_owner, target, m_featureList);
		}

	}
}