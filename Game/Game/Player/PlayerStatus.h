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
			int m_level = 0;					//���x��
			float m_HP = 0.0f;					//HP
			float m_maxHP = 0.0f;				//�ő�HP
			float m_MP = 0.0f;					//MP
			float m_maxMP = 0.0f;				//�ő�MP
			float m_SP = 0.0f;					//SP
			float m_maxSP = 0.0f;				//�ő�SP
			float m_guardGaugeValue = 0.0f;	//�K�[�h�Q�[�W�̒l
			float m_maxGuardGaugeValue = 0.0f;	//�K�[�h�Q�[�W�̍ő�l

			float m_attack = 0.0f;				//�����U����
			float m_intelligence = 0.0f;		//���@�U����
			float m_defence = 0.0f;				//�����h���
			float m_mind = 0.0f;				//���@�h���
		};
	}
}

