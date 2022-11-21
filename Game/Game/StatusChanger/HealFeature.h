#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//‰ñ•œ‚·‚é‚à‚Ì
		enum class EnHealTarget {

			enHP,	//HP
			enMP,	//MP
			enSP,	//SP

			enNone	//İ’è‚È‚µ
		};

		//‰ñ•œ‹@”\
		class HealFeature : public CFeature
		{
		public:
			void Init(IGameActor* target, EnHealTarget healTarget, float healValue);

			void Create();
		private:
			EnHealTarget m_healTarget = EnHealTarget::enNone;	//‰ñ•œ‚·‚é‚à‚Ì
			float m_healValue = 0.0f;			//‰ñ•œ—Ê
			IGameActor* m_target = nullptr;		//‰ñ•œ‘ÎÛ
		};
	}
}

