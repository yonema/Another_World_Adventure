#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//回復するもの
		enum class EnHealTarget {

			enHP,	//HP
			enMP,	//MP
			enSP,	//SP

			enNone = -1	//設定なし
		};

		//回復方法
		enum class EnHowHeal {

			enConst,	//定量
			enRatio,	//割合

			enNone = -1	//設定なし
		};

		//回復機能
		class CHealFeature : public CFeature
		{
		public:
			void Init(EnHealTarget healTarget, EnHowHeal howHeal, float healValue);

			void Create();

		private:
			void CalcHealValue(IGameActor* target, EnHealTarget healTarget, float healValue);

		private:
			EnHealTarget m_healTarget = EnHealTarget::enNone;	//回復するもの
			EnHowHeal m_howHeal = EnHowHeal::enNone;			//回復方法
			float m_healValue = 0.0f;			//回復量
		};
	}
}

