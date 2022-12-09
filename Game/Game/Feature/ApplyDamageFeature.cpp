#include "YonemaEnginePreCompile.h"
#include "ApplyDamageFeature.h"
#include "../GameActor.h"

namespace nsAWA {

	namespace nsFeature {

		namespace {

			//���_�_���[�W�v�Z��
			constexpr float CalcDamage(
				float level,
				float power,
				float attack,
				float deffence
			) {
				return (((level * 2.0f / 5.0f + 2.0f) * power * attack / deffence) / 50.0f + 2.0f) * 10.0f;
			}
		}

		void CApplyDamageFeature::Init(
			int level,
			int power,
			float attack,
			float deffence,
			IGameActor* target,
			bool canGuard
		) {
			//����ݒ�B
			m_level = static_cast<float>(level);
			m_power = static_cast<float>(power);
			m_attack = attack;
			m_deffence = deffence;
			m_target = target;
			m_canGuard = canGuard;
		}

		void CApplyDamageFeature::Create() {

			//�_���[�W�l���������B
			float damage = 0.0f;

			//���_�_���[�W�v�Z���s���B
			damage = CalcDamage(m_level, m_power, m_attack, m_deffence);

			//�����_���l�𐶐��B�i�������j
			float random = 0.0f;
			//���͌Œ��1.0�Ƃ���B
			random = 1.0f;

			//�����l���_���[�W�ɏ�Z�B
			damage *= random;

			//�^�[�Q�b�g�Ƀ_���[�W��^����B
			m_target->ApplyDamage(damage, m_power, m_canGuard);

			//�j���B
			Release();
		}
	}
}