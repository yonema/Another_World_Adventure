#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsPlayer {

		//�v���C���[�X�e�[�^�X�N���X
		class CPlayerStatus : public CStatus
		{
		public:
			void Init();

			void HealHP(float value);
			void DamageHP(float value);

			void HealMP(float value);
			void DamageMP(float value);

			void HealSP(float value);
			void DamageSP(float value);

			void HealGuardGaugeValue(float value);
			void DamageGuardGaugeValue(float value);
		public:
			float GetHP()const {

				return m_HP;
			}
			float GetMaxHP()const {

				return m_maxHP;
			}
			float GetMP()const {

				return m_MP;
			}
			float GetSP()const {

				return m_SP;
			}
			float GetGuardGaugeValue()const {

				return m_guardGaugeValue;
			}
		private:
			float m_HP = 0;					//HP
			float m_maxHP = 0;				//�ő�HP
			float m_MP = 0;					//MP
			float m_maxMP = 0;				//�ő�MP
			float m_SP = 0;					//SP
			float m_maxSP = 0;				//�ő�SP
			float m_guardGaugeValue = 0;	//�K�[�h�Q�[�W�̒l
			float m_maxGuardGaugeValue = 0;	//�K�[�h�Q�[�W�̍ő�l
		};
	}
}

