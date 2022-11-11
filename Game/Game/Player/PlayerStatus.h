#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//�v���C���[�X�e�[�^�X�N���X
		class CPlayerStatus : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void HealHP(int value);
			void DamageHP(int value);

			void HealMP(int value);
			void DamageMP(int value);

			void HealSP(int value);
			void DamageSP(int value);

			void HealGuardGaugeValue(int value);
			void DamageGuardGaugeValue(int value);
		public:
			int GetHP()const {

				return m_HP;
			}
			int GetMP()const {

				return m_MP;
			}
			int GetSP()const {

				return m_SP;
			}
			int GetGuardGaugeValue()const {

				return m_guardGaugeValue;
			}
		private:
			int m_HP = 0;					//HP
			int m_maxHP = 0;				//�ő�HP
			int m_MP = 0;					//MP
			int m_maxMP = 0;				//�ő�MP
			int m_SP = 0;					//SP
			int m_maxSP = 0;				//�ő�SP
			int m_guardGaugeValue = 0;		//�K�[�h�Q�[�W�̒l
			int m_maxGuardGaugeValue = 0;	//�K�[�h�Q�[�W�̍ő�l
		};
	}
}

