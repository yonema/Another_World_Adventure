#include "YonemaEnginePreCompile.h"
#include "MonsterStatus.h"

namespace nsAWA {

	namespace nsMonster {

		namespace {

#ifdef _DEBUG
			//仮の定数。後ほどcsvで入力するコードを書く。
			constexpr const float kLev1MaxHP = 200.0f;			//仮のHP最大値。
			constexpr const float kLev1MaxMP = 100.0f;			//仮のHP最大値。
#endif
		}

		void CMonsterStatus::Init() {

#ifdef _DEBUG
			//今回は仮にレベル１でスタート。
			m_level = 1;

			//今回は仮にHP、最大HPを定数で入力。
			m_HP = kLev1MaxHP / 2.0f;
			m_maxHP = kLev1MaxHP;

			//今回は仮にMP、最大MPを定数で入力。
			m_MP = kLev1MaxMP;
			m_maxMP = kLev1MaxMP;

			//今回は仮に攻撃力を定数で入力。
			m_attack = 20.0f;
#endif
		}

		void CMonsterStatus::HealHP(float value) {

			//HPを上昇させる。
			m_HP += value;

			//最大HPを超えているなら。
			if (m_HP > m_maxHP) {

				//最大HPと同じに設定する。
				m_HP = m_maxHP;
			}
		}

		void CMonsterStatus::DamageHP(float value) {

			//HPを減少させる。
			m_HP -= value;

			//0未満になったら0に設定する。
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}
	}
}