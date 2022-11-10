#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//プレイヤーステータスクラス
		class CPlayerStatus : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void DamageHP(int damage);
		public:
			int GetHP()const {

				return m_HP;
			}
		private:
			int m_HP = 0;		//HP
			int m_maxHP = 0;	//最大HP
		};
	}
}

