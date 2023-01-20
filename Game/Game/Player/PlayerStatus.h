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

			int GetLevel()const {

				return m_level;
			}

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

			float GetAttack(const std::string& attackType)const {

				if (attackType == "Physical") {

					return m_attack;
				}
				else if (attackType == "Magical") {

					return m_intelligence;
				}
				else {

					nsGameWindow::MessageBoxError(L"attackTypeが不適切です。");
					return FLT_MAX;
				}
			}
			float GetDeffence(const std::string& defenceType)const {

				if (defenceType == "Physical") {

					return m_defence;
				}
				else if (defenceType == "Magical") {

					return m_mind;
				}
				else {

					nsGameWindow::MessageBoxError(L"defenceTypeが不適切です。");
					return FLT_MAX;
				}
			}
		private:
			int m_level = 0;					//レベル
			float m_HP = 0.0f;					//HP
			float m_maxHP = 0.0f;				//最大HP
			float m_MP = 0.0f;					//MP
			float m_maxMP = 0.0f;				//最大MP
			float m_SP = 0.0f;					//SP
			float m_maxSP = 0.0f;				//最大SP
			float m_guardGaugeValue = 0.0f;	//ガードゲージの値
			float m_maxGuardGaugeValue = 0.0f;	//ガードゲージの最大値

			float m_attack = 0.0f;				//物理攻撃力
			float m_intelligence = 0.0f;		//魔法攻撃力
			float m_defence = 0.0f;				//物理防御力
			float m_mind = 0.0f;				//魔法防御力
		};
	}
}

