#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//�񕜂������
		enum class EnHealTarget {

			enHP,	//HP
			enMP,	//MP
			enSP,	//SP

			enNone = -1	//�ݒ�Ȃ�
		};

		//�񕜕��@
		enum class EnHowHeal {

			enConst,	//���
			enRatio,	//����

			enNone = -1	//�ݒ�Ȃ�
		};

		//�񕜋@�\
		class CHealFeature : public CFeature
		{
		public:
			void Init(EnHealTarget healTarget, EnHowHeal howHeal, float healValue);

			void Create();

		private:
			void CalcHealValue(IGameActor* target, EnHealTarget healTarget, float healValue);

		private:
			EnHealTarget m_healTarget = EnHealTarget::enNone;	//�񕜂������
			EnHowHeal m_howHeal = EnHowHeal::enNone;			//�񕜕��@
			float m_healValue = 0.0f;			//�񕜗�
		};
	}
}

