#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

#ifdef _DEBUG
		void CActiveSkill::Execute() {

			//効果を発動。
			for (const auto& feature : m_featureList) {

				feature->Create();
			}
		}
#endif

		void CActiveSkill::AddFeature(nsFeature::CFeature* feature) {

			//効果を追加。
			m_featureList.emplace_back(feature);
		}
	}
}