#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"
#include "../CSV/CSVManager.h"
#include "PlayerWeaponManager.h"
#include "../Weapon/Weapon.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/PassiveSkill.h"
#include "../Feature/FeatureManager.h"
#include "../Feature/Feature.h"
#include "../Feature/BuffDebuff.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr float kPlayerWinceDelimiter = 30.0f;	//�v���C���[�̂Ђ�ݒl�̋�؂�i���j
			constexpr float kPerMax = 100.0f;			//�ő偓
			constexpr float kSPValue = 100.0f;			//SP��
			constexpr float kGGValue = 100.0f;			//�K�[�h�Q�[�W��
			constexpr float kStatusBaseInitValue = 0.0f;	//�X�e�[�^�X���f�̂��߂̏����l
			constexpr float kStatusBaseMul = 1.0f;	//�X�e�[�^�X���f�̏����{��
		}

		void CPlayerStatus::Init(const nsWeapon::CWeapon* const & playerWeapon,
			nsSkill::CPassiveSkillManager* passiveSkillManager,
			nsFeature::CFeatureManager* featureManager
		) {

			//�����擾�B
			m_weapon = &playerWeapon;
			m_passiveSkillManager = passiveSkillManager;
			m_featureManager = featureManager;

			//�X�e�[�^�X���f�̂��߂̃��X�g���������B
			ResetStatusList();
#ifdef _DEBUG

			m_attack = 0.0f;

			m_intelligence = 2.0f;

			m_defence = 2.0f;
			m_mind = 2.0f;
#endif
			
		}

		void CPlayerStatus::Update() {

			std::list<nsFeature::CFeature*> featureList;

			//�p�b�V�u�X�L���̌��ʂ̃��X�g�����ɎQ�ƁB
			//for (const auto& passiveSkill : m_passiveSkillManager->GetPassiveSkillList()) {
			//
			//	//�p�b�V�u�X�L�����o�^����Ă��Ȃ�������B
			//	if (passiveSkill == nullptr) {
			//
			//		//���ցB
			//		continue;
			//	}
			//
			//	for (const auto& feature : passiveSkill->GetFeatureList()) {
			//
			//		//���ʂ̃N���X�����擾�B
			//		const type_info& id = typeid(*feature);
			//
			//		//�o�t�f�o�t�Ȃ�B
			//		if (typeid(nsFeature::nsStatusChanger::CBuffDebuff) == id) {
			//
			//			//���ʂ̃��X�g�����Ɏ擾�B
			//			featureList.emplace_back(feature);
			//		}
			//	}
			//}

			//�X�e�[�^�X�ω��̃��X�g�����ɎQ�ƁB
			for (const auto& feature : m_featureManager->GetStatusChanger()) {

				//���ʂ̃N���X�����擾�B
				const type_info& id = typeid(*feature);

				//�o�t�f�o�t�Ȃ�B
				if (typeid(nsFeature::nsStatusChanger::CBuffDebuff) == id) {

					//���ʂ̃��X�g�����Ɏ擾�B
					featureList.emplace_back(feature);
				}
			}

			//�X�e�[�^�X���f�̂��߂̃f�[�^���������B
			ResetStatusList();

			//�o�t�f�o�t�ʂ��v�Z���ĉ����f�B
			//�X�e�[�^�X�f�[�^�����ɎQ�ƁB
			for (int statusRef = 0; statusRef < static_cast<int>(nsFeature::EnStatusRef::enNum); statusRef++) {

				//�o�t�f�o�t���X�g����l���󂯎��B
				for (const auto& feature : featureList) {

					auto featureRef = dynamic_cast<nsFeature::nsStatusChanger::CBuffDebuff*>(feature);

					//�܂����Z�B
					m_statusBaseList[statusRef] += featureRef->Apply(static_cast<nsFeature::EnStatusRef>(statusRef));
				}
			}

			//�e�X�e�[�^�X��{���f�B
			m_attack = (*m_weapon)->GetAttack() * (kStatusBaseMul + m_statusBaseList[static_cast<int>(nsFeature::EnStatusRef::enAttack)]);


			m_intelligence = (*m_weapon)->GetIntelligence() * m_statusBaseList[static_cast<int>(nsFeature::EnStatusRef::enInteligence)];
		}

		void CPlayerStatus::LoadStatus(const std::vector<std::string>& statusDataStr) {

			//�X�e�[�^�X�����[�h�B
			m_level = std::stoi(statusDataStr[0]);
			m_HP = std::stof(statusDataStr[1]);
			m_maxHP = std::stof(statusDataStr[2]);
			m_MP = std::stof(statusDataStr[3]);
			m_maxMP = std::stof(statusDataStr[4]);
			m_SP = kSPValue;
			m_maxSP = kSPValue;
			m_guardGaugeValue = kGGValue;
			m_maxGuardGaugeValue = kGGValue;
			m_winceValue = 0.0f;

			//�v���C���[�̂Ђ�ݒl�̋�؂��ݒ�B
			m_winceDelimiter = m_maxHP * kPlayerWinceDelimiter / kPerMax;
		}

		void CPlayerStatus::ResetStatusList() {

			//�X�e�[�^�X���f�̂��߂̃f�[�^���������B
			for (auto& statusBase : m_statusBaseList) {

				statusBase = kStatusBaseInitValue;
			}
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