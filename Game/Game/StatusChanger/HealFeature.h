#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//回復するもの
		enum class EnHealTarget {

			enHP,	//HP
			enMP,	//MP
			enSP,	//SP

			enNone	//設定なし
		};

		//回復機能
		class HealFeature : public CFeature
		{
		public:
			void Init(IGameActor* target, EnHealTarget healTarget, float healValue);

			void Create();
		private:
			EnHealTarget m_healTarget = EnHealTarget::enNone;	//回復するもの
			float m_healValue = 0.0f;			//回復量
			IGameActor* m_target = nullptr;		//回復対象
		};
	}
}

