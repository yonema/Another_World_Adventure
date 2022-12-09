#include "YonemaEnginePreCompile.h"
#include "HealFeature.h"
#include "../GameActor.h"
#include "../Status.h"

namespace nsAWA {

	namespace nsFeature {

		namespace {

			constexpr float kMaxPer = 100.0f;	//�ő偓
		}

		void CHealFeature::Init(EnHealTarget healTarget, EnHowHeal howHeal, float healValue) {

			//����ݒ�B
			m_healTarget = healTarget;
			m_howHeal = howHeal;
			m_healValue = healValue;
		}

		void CHealFeature::Create() {

			switch (m_healTarget) {

				//HP�񕜁B
			case EnHealTarget::enHP:
				m_target->HealHP(m_healValue);
				break;

				//MP�񕜁B
			case EnHealTarget::enMP:
				m_target->HealMP(m_healValue);
				break;

				//SP�񕜁B
			case EnHealTarget::enSP:
				m_target->HealSP(m_healValue);
				break;
			}

			//�j���B
			Release();
		}

		void CHealFeature::CalcHealValue(IGameActor* target, EnHealTarget healTarget, float healValue) {

			CStatus* status = target->GetStatus();

			switch (healTarget) {

			case EnHealTarget::enHP:
				m_healValue = (status->GetMaxHP() / kMaxPer) * healValue;
				break;
			case EnHealTarget::enMP:
				m_healValue = (status->GetMaxMP() / kMaxPer) * healValue;
				break;
			case EnHealTarget::enSP:
				m_healValue = (status->GetMaxSP() / kMaxPer) * healValue;
				break;
			}
		}
	}
}