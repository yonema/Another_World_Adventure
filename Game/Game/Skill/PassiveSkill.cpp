#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

		namespace {

			constexpr float kPassiveSkillDurationTime = 999.9f;	//パッシブスキル内の効果の持続時間
		}

		void CPassiveSkill::ReleaseFeature() {

			//効果を順に参照。
			for (const auto& feature : m_featureList) {

				//効果を破棄。
				feature->End();
			}
		}

		void CPassiveSkill::Update() {

			//効果を順に参照。
			for (const auto& feature : m_featureList) {

				//効果の持続時間を更新。
				feature->SetDurationTime(kPassiveSkillDurationTime);
			}
		}
	}
}