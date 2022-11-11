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
		public:
			int GetHP()const {

				return m_HP;
			}
			int GetMP()const {

				return m_MP;
			}
		private:
			int m_HP = 0;		//HP
			int m_maxHP = 0;	//�ő�HP
			int m_MP = 0;		//MP
			int m_maxMP = 0;	//�ő�MP
		};
	}
}

