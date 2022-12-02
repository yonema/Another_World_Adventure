#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsPlayer {

		//プレイヤーステータスクラス
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

				//最大MPをリターン。
				return m_maxMP;
			}
			float GetSP()const {

				return m_SP;
			}
			float GetMaxSP()const {

				//最大SPをリターン。
				return m_maxSP;
			}
			float GetGuardGaugeValue()const {

				return m_guardGaugeValue;
			}
			float GetMaxGuardGaugeValue()const {

				//ガードゲージの最大値をリターン。
				return m_maxGuardGaugeValue;
			}
		private:
			float m_HP = 0;					//HP
			float m_maxHP = 0;				//最大HP
			float m_MP = 0;					//MP
			float m_maxMP = 0;				//最大MP
			float m_SP = 0;					//SP
			float m_maxSP = 0;				//最大SP
			float m_guardGaugeValue = 0;	//ガードゲージの値
			float m_maxGuardGaugeValue = 0;	//ガードゲージの最大値
		};
	}
}

