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

			void SetUseMP(float useMP) {

				//消費MPを設定。
				m_useMP = useMP;
			}

			float GetUseMP() {

				//消費MPをリターン。
				return m_useMP;
			}
#ifdef _DEBUG
			void Execute();
#endif
		private:
			const char* m_animationName = nullptr;		//アニメーションの名前
			float m_useMP = 0.0f;	//消費MP
		};
	}
}

