#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "Poison.h"
#include "../../Status.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			namespace {

				constexpr float kPoisonPower = 1.0f;		//�ł̋����i��/s�j
				constexpr float kPoisonMaxPower = 100.0f;	//�ł̍ő�̋����i���j
			}

			void CPoison::Init() {

				//�^�[�Q�b�g�̍ő�HP���擾����B
				m_targetMaxHP = m_target->GetStatus()->GetMaxHP();
			}

			void CPoison::ExecuteAtStart(float deltaTime) {

				//�ł̈З͂��v�Z�B
				float damageAmount = m_targetMaxHP * (kPoisonPower / kPoisonMaxPower);

				//�^����_���[�W�ʂ��v�Z�B
				float poisonPower = damageAmount * deltaTime;

				//�_���[�W��~����B
				//m_damageTank += poisonPower;

				//�^�[�Q�b�g�ɃK�[�h�s�̃_���[�W��^����B
				m_target->ApplyDamage(
					poisonPower,
					false			//canGuard
				);
			}
		}
	}
}
