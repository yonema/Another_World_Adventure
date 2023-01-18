#include "YonemaEnginePreCompile.h"
#include "MonsterStatus.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

#ifdef _DEBUG
			//���̒萔�B��ق�csv�œ��͂���R�[�h�������B
			constexpr const float kLev1MaxHP = 200.0f;			//����HP�ő�l�B
			constexpr const float kLev1MaxMP = 100.0f;			//����HP�ő�l�B
#endif
		}

		void CMonsterStatus::Init() {

#ifdef _DEBUG
			//����͉��Ƀ��x���P�ŃX�^�[�g�B
			m_level = 1;

			//����͉���HP�A�ő�HP��萔�œ��́B
			m_HP = kLev1MaxHP / 2.0f;
			m_maxHP = kLev1MaxHP;

			//����͉���MP�A�ő�MP��萔�œ��́B
			m_MP = kLev1MaxMP;
			m_maxMP = kLev1MaxMP;

			//����͉��ɍU���͂�萔�œ��́B
			m_attack = 20.0f;
#endif
		}

		void CMonsterStatus::HealHP(float value) {

			//HP���㏸������B
			m_HP += value;

			//�ő�HP�𒴂��Ă���Ȃ�B
			if (m_HP > m_maxHP) {

				//�ő�HP�Ɠ����ɐݒ肷��B
				m_HP = m_maxHP;
			}
		}

		void CMonsterStatus::DamageHP(float value) {

			//HP������������B
			m_HP -= value;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}
	}
}