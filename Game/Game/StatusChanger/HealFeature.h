#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//�񕜂������
		enum class EnHealTarget {

			enHP,	//HP
			enMP,	//MP
			enSP,	//SP

			enNone	//�ݒ�Ȃ�
		};

		//�񕜋@�\
		class HealFeature : public CFeature
		{
		public:
			void Init(IGameActor* target, EnHealTarget healTarget, float healValue);

			void Create();
		private:
			EnHealTarget m_healTarget = EnHealTarget::enNone;	//�񕜂������
			float m_healValue = 0.0f;			//�񕜗�
			IGameActor* m_target = nullptr;		//�񕜑Ώ�
		};
	}
}

