#include "YonemaEnginePreCompile.h"
#include "ActiveSkill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

#ifdef _DEBUG
		void CActiveSkill::Execute() {

			//���ʂ𔭓��B
			for (const auto& feature : m_featureList) {

				feature->Create();
			}
		}
#endif

		void CActiveSkill::AddFeature(nsFeature::CFeature* feature) {

			//���ʂ�ǉ��B
			m_featureList.emplace_back(feature);
		}
	}
}