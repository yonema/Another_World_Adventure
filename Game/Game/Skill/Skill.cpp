#include "YonemaEnginePreCompile.h"
#include "Skill.h"
#include "../Feature/Feature.h"

namespace nsAWA {

	namespace nsSkill {

		void CSkill::Create(nsFeature::CFeature* feature) {

			//���ʂ𔭓��B
			feature->Create();
		}
	}
}