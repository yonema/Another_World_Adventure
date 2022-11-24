#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//パッシブスキル
		class CPassiveSkill : public CSkill
		{
		public:
			void AddFeature(nsFeature::CFeature* feature);

			void Update();
		};
	}
}

