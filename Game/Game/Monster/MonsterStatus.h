#pragma once
#include "../Status.h"

namespace nsAWA {

	namespace nsMonster {

		//�����X�^�[�X�e�[�^�X
		class CMonsterStatus : public CStatus
		{
		public:
			void Init(const std::string& monsterName);

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

			float GetAttack(const std::string& attackType)const {

				if (attackType == "Physical") {

					return m_attack;
				}
				else if (attackType == "Magical") {

					return m_intelligence;
				}
				else {

					nsGameWindow::MessageBoxError(L"attackType���s�K�؂ł��B");
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

					nsGameWindow::MessageBoxError(L"defenceType���s�K�؂ł��B");
					return FLT_MAX;
				}
			}

		private:
			int m_level = 0;
			float m_HP = 0.0f;
			float m_maxHP = 0.0f;

			float m_attack = 0.0f;				//�����U����
			float m_intelligence = 0.0f;		//���@�U����
			float m_defence = 0.0f;				//�����h���
			//float m_defence = 0.0f;				//�����h���
			float m_mind = 0.0f;				//���@�h���
		};
	}
}

