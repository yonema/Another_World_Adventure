#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr float kPassiveSkillDurationTime = 0.1f;	//パッシブスキル内の効果の持続時間
		}

		void CPassiveSkill::Update() {

			//効果を順に参照。
			for (const auto& feature : m_featureList) {

				//効果の持続時間を更新。
				feature->SetDurationTime(kPassiveSkillDurationTime);
			}
		}

		void CPassiveSkill::AddFeature(nsFeature::CFeature* feature) {

			//効果を追加。
			m_featureList.emplace_back(feature->CreateAndReturn());
		}
	}
}