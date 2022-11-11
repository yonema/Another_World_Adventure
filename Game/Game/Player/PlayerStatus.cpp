#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

#ifdef _DEBUG
			//���̒萔�B��ق�csv�œ��͂���R�[�h�������B
			constexpr const int kLev1MaxHP = 200;			//����HP�ő�l�B
			constexpr const int kLev1MaxMP = 100;			//����HP�ő�l�B
			constexpr const int kMaxSP = 100;				//SP�ő�l�B
			constexpr const int kMaxGuardGaugeValue = 100;	//�K�[�h�Q�[�W�̍ő�l�B
#endif
		}

		void CPlayerStatus::Init() {

			//�X�e�[�^�X���[�h�����B
			//LoadStatus();
			//...
#ifdef _DEBUG
			//����͉���HP�A�ő�HP��萔�œ��́B
			m_HP = kLev1MaxHP;
			m_maxHP = kLev1MaxHP;

			//����͉���MP�A�ő�MP��萔�œ��́B
			m_MP = kLev1MaxMP;
			m_maxMP = kLev1MaxMP;
#endif
			//SP��ݒ�B
			m_SP = kMaxSP;
			m_maxSP = kMaxSP;

			//�K�[�h�Q�[�W�̒l��ݒ�B
			m_guardGaugeValue = kMaxGuardGaugeValue;
			m_maxGuardGaugeValue = kMaxGuardGaugeValue;
		}

		void CPlayerStatus::HealHP(int value) {

			//HP���㏸������B
			m_HP += value;

			//�ő�HP�𒴂��Ă���Ȃ�B
			if (m_HP > m_maxHP) {

				//�ő�HP�Ɠ����ɐݒ肷��B
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(int value) {

			//HP������������B
			m_HP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_HP < 0) {

				m_HP = 0;
			}
		}

		void CPlayerStatus::HealMP(int value) {

			//MP���㏸������B
			m_MP += value;

			//�ő�MP�𒴂��Ă���Ȃ�B
			if (m_MP > m_maxMP) {

				//�ő�MP�Ɠ����ɐݒ肷��B
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(int value) {

			//MP������������B
			m_MP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_MP < 0) {

				m_MP = 0;
			}
		}

		void CPlayerStatus::HealSP(int value) {

			//SP���㏸������B
			m_SP += value;

			//�ő�SP�𒴂��Ă���Ȃ�B
			if (m_SP > m_maxSP) {

				//�ő�SP�Ɠ����ɐݒ肷��B
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(int value) {

			//SP������������B
			m_SP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_SP < 0) {

				m_SP = 0;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(int value) {

			//�K�[�h�Q�[�W�̒l���㏸������B
			m_guardGaugeValue += value;

			//�K�[�h�Q�[�W�̍ő�l�𒴂��Ă���Ȃ�B
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//�K�[�h�Q�[�W�̍ő�l�Ɠ����ɐݒ肷��B
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(int value) {

			//�K�[�h�Q�[�W�̒l������������B
			m_guardGaugeValue -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_guardGaugeValue < 0) {

				m_guardGaugeValue = 0;
			}
		}
	}
}