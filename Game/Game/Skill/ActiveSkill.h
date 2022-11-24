#pragma once
#include "Skill.h"

namespace nsAWA {

	namespace nsSkill {

		//アクティブスキル
		class CActiveSkill : public CSkill
		{
		public:
			void SetAnimationName(const char* animationName) {

				//対応するスキルのアニメーションの名前を設定。
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

