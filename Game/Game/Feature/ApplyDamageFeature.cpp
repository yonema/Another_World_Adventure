#include "YonemaEnginePreCompile.h"
#include "ApplyDamageFeature.h"
#include "../GameActor.h"
#include "../Status.h"

namespace nsAWA {

	namespace nsFeature {

		namespace {
			constexpr float kMaxPer = 100.0f;	//�ő偓
			constexpr float kRandomDamageMax = 1.0f;	//�ő�Η͔{��
			constexpr float kRandomDamageMin = 0.85f;	//�Œ�Η͔{��

			//���_�_���[�W�v�Z��
			constexpr float CalcDamage(
				int level,
				float power,
				float attack,
				float deffence
			) {
				return (((level * 2.0f / 5.0f + 2.0f) * power * attack / deffence) / 50.0f + 2.0f) * 10.0f;
			}
		}

		void CApplyDamageFeature::Init(IGameActor* creator, IGameActor* target, float power, const std::string& attackType, bool canGuard) {

			//�����҂̏�񂪂Ȃ��Ȃ�
			if (creator == nullptr) {

				//�x�����o�́B
				nsGameWindow::MessageBoxError(L"�����҂̏�񂪐ݒ肳��Ă��܂���B");
			}

			//�_���[�W��^����̂ɕK�v�ȏ����擾�B
			int level = creator->GetStatus()->GetLevel();
			float attack = creator->GetStatus()->GetAttack(attackType);
			float defence = target->GetStatus()->GetDeffence(attackType);

			//�^�[�Q�b�g��ݒ�B
			m_target = target;

			//�_���[�W�v�Z�B
			m_damage = CalcDamage(level, power, attack, defence);

			//�����l�𐶐��B
			nsUtils::CRandom random;
			float randomDamage = random.GetRangeFloat(kRandomDamageMin, kRandomDamageMax);

			//�����l���_���[�W�ɏ�Z�B
			m_damage *= randomDamage;

			//�K�[�h�ł��邩�ǂ�����ݒ�B
			m_canGuard = canGuard;
		}

		void CApplyDamageFeature::Init(const std::string& damageType, IGameActor* target, float damage, bool canGuard) {

			//�萔�_���[�W��ݒ�B
			if (damageType == "Const") {

				m_damage = damage;
			}
			//�����_���[�W��ݒ�B
			else if (damageType == "Ratio") {

				m_damage = (target->GetStatus()->GetMaxHP() / kMaxPer) * damage;
			}
			//����ȊO�Ȃ�
			else {

				//�x�����o�́B
				nsGameWindow::MessageBoxError(L"�_���[�W�^�C�v�̐ݒ肪�s�K�؂ł��B");
			}

			//�^�[�Q�b�g��ݒ�B
			m_target = target;

			//�K�[�h�ł��邩�ǂ�����ݒ�B
			m_canGuard = canGuard;
		}

		void CApplyDamageFeature::Create() {

			//�^�[�Q�b�g�Ƀ_���[�W��^����B
			m_target->ApplyDamage(m_damage, m_power, m_canGuard);

			//���҂��q�b�g�X�g�b�v�B
			m_target->HitStop(0.1f);

			m_creator->HitStop(0.1f);

			//�j���B
			Release();
		}
	}
}