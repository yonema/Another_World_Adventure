#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

#ifdef _DEBUG
			//仮の定数。後ほどcsvで入力するコードを書く。
			constexpr const int kLev1MaxHP = 200;		//仮のHP最大値。
#endif
		}

		void CPlayerStatus::Init() {

			//ステータスロード処理。
			//LoadStatus();
			//...
#ifdef _DEBUG
			//今回は仮にHP、最大HPを定数で入力。
			m_HP = kLev1MaxHP;
			m_maxHP = kLev1MaxHP;
#endif
		}

		void CPlayerStatus::DamageHP(int damage) {

			//HPダメージを受ける。
			m_HP -= damage;

			//0未満になったら0に設定する。
			if (m_HP <= 0) {

				m_HP = 0;
			}
		}
	}
}