#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsMonster {

		//モンスターステータス
		class CMonsterStatus : public CStatus
		{
		public:
			void Init();

			void HealHP(float value);
			void DamageHP(float value);

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

				return m_maxMP;
			}
			float GetSP()const {

				return m_SP;
			}
			float GetMaxSP()const {

				return m_maxSP;
			}

			float GetAttack(const std::string& attackType)const {

				if (attackType == "Physical") {

					return m_attack;
				}
				else if (attackType == "magic") {

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
				else if (defenceType == "magic") {

					return m_mind;
				}
				else {

					nsGameWindow::MessageBoxError(L"defenceTypeが不適切です。");
					return FLT_MAX;
				}
			}

		private:
			int m_level = 0;
			float m_HP = 0.0f;
			float m_maxHP = 0.0f;
			float m_MP = 0.0f;
			float m_maxMP = 0.0f;
			float m_SP = 0.0f;
			float m_maxSP = 0.0f;

			float m_attack = 0.0f;				//物理攻撃力
			float m_intelligence = 0.0f;		//魔法攻撃力
#ifdef _DEBUG
			float m_defence = 20.0f;				//物理防御力
#endif
			//float m_defence = 0.0f;				//物理防御力
			float m_mind = 0.0f;				//魔法防御力
		};
	}
}

