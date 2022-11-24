#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

#ifdef _DEBUG
		void CActiveSkill::Execute() {

			//Œø‰Ê‚ğ”­“®B
			for (const auto& feature : m_featureList) {

				feature->Create();
			}
		}
#endif

		void CActiveSkill::AddFeature(nsFeature::CFeature* feature) {

			//Œø‰Ê‚ğ’Ç‰ÁB
			m_featureList.emplace_back(feature);
		}
	}
}