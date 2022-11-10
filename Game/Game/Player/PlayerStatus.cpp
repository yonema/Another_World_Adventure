#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

#ifdef _DEBUG
			//���̒萔�B��ق�csv�œ��͂���R�[�h�������B
			constexpr const int kLev1MaxHP = 200;		//����HP�ő�l�B
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
#endif
		}

		void CPlayerStatus::DamageHP(int damage) {

			//HP�_���[�W���󂯂�B
			m_HP -= damage;

			//0�����ɂȂ�����0�ɐݒ肷��B
			if (m_HP <= 0) {

				m_HP = 0;
			}
		}
	}
}