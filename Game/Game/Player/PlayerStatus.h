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
			float GetMaxMP()const {

				//�ő�MP�����^�[���B
				return m_maxMP;
			}
			float GetSP()const {

				return m_SP;
			}
			float GetMaxSP()const {

				//�ő�SP�����^�[���B
				return m_maxSP;
			}
			float GetGuardGaugeValue()const {

				return m_guardGaugeValue;
			}
			float GetMaxGuardGaugeValue()const {

				//�K�[�h�Q�[�W�̍ő�l�����^�[���B
				return m_maxGuardGaugeValue;
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

