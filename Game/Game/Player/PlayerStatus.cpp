#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

#ifdef _DEBUG
			//���̒萔�B��ق�csv�œ��͂���R�[�h�������B
			constexpr const float kLev1MaxHP = 200.0f;			//����HP�ő�l�B
			constexpr const float kLev1MaxMP = 100.0f;			//����HP�ő�l�B
			constexpr const float kMaxSP = 100.0f;				//SP�ő�l�B
			constexpr const float kMaxGuardGaugeValue = 100.0f;	//�K�[�h�Q�[�W�̍ő�l�B
#endif
		}

		void CPlayerStatus::Init() {

			//�X�e�[�^�X���[�h�����B
			//LoadStatus();
			//...
#ifdef _DEBUG
			//����͉��Ƀ��x���P�ŃX�^�[�g�B
			m_level = 1;

			//����͉���HP�A�ő�HP��萔�œ��́B
			m_HP = kLev1MaxHP / 2.0f;
			m_maxHP = kLev1MaxHP;

			//����͉���MP�A�ő�MP��萔�œ��́B
			m_MP = kLev1MaxMP;
			m_maxMP = kLev1MaxMP;

			m_attack = 20.0f;

			m_intelligence = 20.0f;
#endif
			//SP��ݒ�B
			m_SP = kMaxSP;
			m_maxSP = kMaxSP;

			//�K�[�h�Q�[�W�̒l��ݒ�B
			m_guardGaugeValue = kMaxGuardGaugeValue;
			m_maxGuardGaugeValue = kMaxGuardGaugeValue;
		}

		void CPlayerStatus::HealHP(float value) {

			//HP���㏸������B
			m_HP += value;

			//�ő�HP�𒴂��Ă���Ȃ�B
			if (m_HP > m_maxHP) {

				//�ő�HP�Ɠ����ɐݒ肷��B
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(float value) {

			//HP������������B
			m_HP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}

		void CPlayerStatus::HealMP(float value) {

			//MP���㏸������B
			m_MP += value;

			//�ő�MP�𒴂��Ă���Ȃ�B
			if (m_MP > m_maxMP) {

				//�ő�MP�Ɠ����ɐݒ肷��B
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(float value) {

			//MP������������B
			m_MP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_MP < 0.0f) {

				m_MP = 0.0f;
			}
		}

		void CPlayerStatus::HealSP(float value) {

			//SP���㏸������B
			m_SP += value;

			//�ő�SP�𒴂��Ă���Ȃ�B
			if (m_SP > m_maxSP) {

				//�ő�SP�Ɠ����ɐݒ肷��B
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(float value) {

			//SP������������B
			m_SP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_SP < 0.0f) {

				m_SP = 0.0f;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(float value) {

			//�K�[�h�Q�[�W�̒l���㏸������B
			m_guardGaugeValue += value;

			//�K�[�h�Q�[�W�̍ő�l�𒴂��Ă���Ȃ�B
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//�K�[�h�Q�[�W�̍ő�l�Ɠ����ɐݒ肷��B
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(float value) {

			//�K�[�h�Q�[�W�̒l������������B
			m_guardGaugeValue -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_guardGaugeValue < 0.0f) {

				m_guardGaugeValue = 0.0f;
			}
		}
	}
}