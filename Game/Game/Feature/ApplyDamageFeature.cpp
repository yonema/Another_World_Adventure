#include "YonemaEnginePreCompile.h"
#include "ApplyDamageFeature.h"
#include "../GameActor.h"

namespace nsAWA {

	namespace nsFeature {

		namespace {

			//理論ダメージ計算式
			constexpr float CalcDamage(
				float level,
				float power,
				float attack,
				float deffence
			) {
				return (((level * 2.0f / 5.0f + 2.0f) * power * attack / deffence) / 50.0f + 2.0f) * 10.0f;
			}
		}

		void CApplyDamageFeature::Init(
			int level,
			int power,
			float attack,
			float deffence,
			IGameActor* target,
			bool canGuard
		) {
			//情報を設定。
			m_level = static_cast<float>(level);
			m_power = static_cast<float>(power);
			m_attack = attack;
			m_deffence = deffence;
			m_target = target;
			m_canGuard = canGuard;
		}

		void CApplyDamageFeature::Create() {

			//ダメージ値を初期化。
			float damage = 0.0f;

			//理論ダメージ計算を行う。
			damage = CalcDamage(m_level, m_power, m_attack, m_deffence);

			//ランダム値を生成。（未実装）
			float random = 0.0f;
			//今は固定で1.0とする。
			random = 1.0f;

			//乱数値をダメージに乗算。
			damage *= random;

			//ターゲットにダメージを与える。
			m_target->ApplyDamage(damage, m_power, m_canGuard);

			//破棄。
			Release();
		}
	}
}