#include "YonemaEnginePreCompile.h"
#include "PlayerStatus.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

#ifdef _DEBUG
			//仮の定数。後ほどcsvで入力するコードを書く。
			constexpr const float kLev1MaxHP = 200.0f;			//仮のHP最大値。
			constexpr const float kLev1MaxMP = 100.0f;			//仮のHP最大値。
			constexpr const float kMaxSP = 100.0f;				//SP最大値。
			constexpr const float kMaxGuardGaugeValue = 100.0f;	//ガードゲージの最大値。
#endif
		}

		void CPlayerStatus::Init() {

			//ステータスロード処理。
			//LoadStatus();
			//...
#ifdef _DEBUG
			//今回は仮にレベル１でスタート。
			m_level = 1;

			//今回は仮にHP、最大HPを定数で入力。
			m_HP = kLev1MaxHP / 2.0f;
			m_maxHP = kLev1MaxHP;

			//今回は仮にMP、最大MPを定数で入力。
			m_MP = kLev1MaxMP;
			m_maxMP = kLev1MaxMP;

			m_attack = 20.0f;

			m_intelligence = 20.0f;
#endif
			//SPを設定。
			m_SP = kMaxSP;
			m_maxSP = kMaxSP;

			//ガードゲージの値を設定。
			m_guardGaugeValue = kMaxGuardGaugeValue;
			m_maxGuardGaugeValue = kMaxGuardGaugeValue;
		}

		void CPlayerStatus::HealHP(float value) {

			//HPを上昇させる。
			m_HP += value;

			//最大HPを超えているなら。
			if (m_HP > m_maxHP) {

				//最大HPと同じに設定する。
				m_HP = m_maxHP;
			}
		}

		void CPlayerStatus::DamageHP(float value) {

			//HPを減少させる。
			m_HP -= value;

			//0未満になったら0に設定する。
			if (m_HP < 0.0f) {

				m_HP = 0.0f;
			}
		}

		void CPlayerStatus::HealMP(float value) {

			//MPを上昇させる。
			m_MP += value;

			//最大MPを超えているなら。
			if (m_MP > m_maxMP) {

				//最大MPと同じに設定する。
				m_MP = m_maxMP;
			}
		}

		void CPlayerStatus::DamageMP(float value) {

			//MPを減少させる。
			m_MP -= value;

			//0未満になったら0に設定する。
			if (m_MP < 0.0f) {

				m_MP = 0.0f;
			}
		}

		void CPlayerStatus::HealSP(float value) {

			//SPを上昇させる。
			m_SP += value;

			//最大SPを超えているなら。
			if (m_SP > m_maxSP) {

				//最大SPと同じに設定する。
				m_SP = m_maxSP;
			}
		}

		void CPlayerStatus::DamageSP(float value) {

			//SPを減少させる。
			m_SP -= value;

			//0未満になったら0に設定する。
			if (m_SP < 0.0f) {

				m_SP = 0.0f;
			}
		}

		void CPlayerStatus::HealGuardGaugeValue(float value) {

			//ガードゲージの値を上昇させる。
			m_guardGaugeValue += value;

			//ガードゲージの最大値を超えているなら。
			if (m_guardGaugeValue > m_maxGuardGaugeValue) {

				//ガードゲージの最大値と同じに設定する。
				m_guardGaugeValue = m_maxGuardGaugeValue;
			}
		}

		void CPlayerStatus::DamageGuardGaugeValue(float value) {

			//ガードゲージの値を減少させる。
			m_guardGaugeValue -= value;

			//0未満になったら0に設定する。
			if (m_guardGaugeValue < 0.0f) {

				m_guardGaugeValue = 0.0f;
			}
		}
	}
}