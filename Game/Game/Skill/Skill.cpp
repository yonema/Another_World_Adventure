#include "YonemaEnginePreCompile.h"
#include "Skill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

		void CSkill::Create(nsFeature::CFeature* feature) {

			//効果を発動。
			feature->Create();
		}
	}
}