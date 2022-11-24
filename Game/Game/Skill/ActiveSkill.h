#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//�A�N�e�B�u�X�L��
		class CActiveSkill : public CSkill
		{
		public:
			void SetAnimationName(const char* animationName) {

				//�Ή�����X�L���̃A�j���[�V�����̖��O��ݒ�B
				m_animationName = animationName;
			}

			void AddFeature(nsFeature::CFeature* feature);
#ifdef _DEBUG
			void Execute();
#endif
		private:
			const char* m_animationName = nullptr;
		};
	}
}

