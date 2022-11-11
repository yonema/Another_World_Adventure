#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

#ifdef _DEBUG
			//仮の定数。後ほどcsvで入力するコードを書く。
			constexpr const int kLev1MaxHP = 200;			//仮のHP最大値。
			constexpr const int kLev1MaxMP = 100;			//仮のHP最大値。
			constexpr const int kMaxSP = 100;				//SP最大値。
			constexpr const int kMaxGuardGaugeValue = 100;	//ガードゲージの最大値。
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

			//今回は仮にMP、最大MPを定数で入力。
			m_MP = kLev1MaxMP;
			m_maxMP = kLev1MaxMP;
#endif
			//SPを設定。
			m_SP = kMaxSP;
			m_maxSP = kMaxSP;

			//ガードゲージの値を設定。
			m_guardGaugeValue = kMaxGuardGaugeValue;
			m_maxGuardGaugeValue = kMaxGuardGaugeValue;
		}

		void CPlayerStatus::HealHP(int value) {

			//HPを上昇させる。
			m_HP += value;

			//最大HPを超えているなら。
			if (m_HP > m_maxHP) {

				//最大HPと同じに設定する。
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(int value) {

			//HPを減少させる。
			m_HP -= value;

			//0未満になったら0に設定する。
			if (m_HP < 0) {

				m_HP = 0;
			}
		}

		void CPlayerStatus::HealMP(int value) {

			//MPを上昇させる。
			m_MP += value;

			//最大MPを超えているなら。
			if (m_MP > m_maxMP) {

				//最大MPと同じに設定する。
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(int value) {

			//MPを減少させる。
			m_MP -= value;

			//0未満になったら0に設定する。
			if (m_MP < 0) {

				m_MP = 0;
			}
		}

		void CPlayerStatus::HealSP(int value) {

			//SPを上昇させる。
			m_SP += value;

			//最大SPを超えているなら。
			if (m_SP > m_maxSP) {

				//最大SPと同じに設定する。
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(int value) {

			//SPを減少させる。
			m_SP -= value;

			//0未満になったら0に設定する。
			if (m_SP < 0) {

				m_SP = 0;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(int value) {

			//ガードゲージの値を上昇させる。
			m_guardGaugeValue += value;

			//ガードゲージの最大値を超えているなら。
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//ガードゲージの最大値と同じに設定する。
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(int value) {

			//ガードゲージの値を減少させる。
			m_guardGaugeValue -= value;

			//0未満になったら0に設定する。
			if (m_guardGaugeValue < 0) {

				m_guardGaugeValue = 0;
			}
		}
	}
}