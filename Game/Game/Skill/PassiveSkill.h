#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//�p�b�V�u�X�L��
		class CPassiveSkill : public CSkill
		{
		public:
			void AddFeature(nsFeature::CFeature* feature);

			void Update();
		};
	}
}

