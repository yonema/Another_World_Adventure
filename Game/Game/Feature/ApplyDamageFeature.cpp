#include "YonemaEnginePreCompile.h"
#include "ApplyDamageFeature.h"
#include "../GameActor.h"
#include "../Status.h"

namespace nsAWA {

	namespace nsFeature {

		namespace {
			constexpr float kMaxPer = 100.0f;	//最大％

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

		void CApplyDamageFeature::Init(IGameActor* creator, IGameActor* target, float power, const std::string& attackType, bool canGuard) {

			//生成者の情報がないなら
			if (creator == nullptr) {

				//警告を出力。
				nsGameWindow::MessageBoxError(L"生成者の情報が設定されていません。");
			}

			//ダメージを与えるのに必要な情報を取得。
			int level = creator->GetStatus()->GetLevel();
			float attack = creator->GetStatus()->GetAttack(attackType);
			float defence = target->GetStatus()->GetDeffence(attackType);

			//ターゲットを設定。
			m_target = target;

			//ダメージ計算。
			m_damage = CalcDamage(level, power, attack, defence);

			//ランダム値を生成。（未実装）
			float random = 0.0f;

			//今は固定で1.0とする。
			random = 1.0f;

			//乱数値をダメージに乗算。
			m_damage *= random;

			//ガードできるかどうかを設定。
			m_canGuard = canGuard;
		}

		void CApplyDamageFeature::Init(const std::string& damageType, IGameActor* target, float damage, bool canGuard) {

			//定数ダメージを設定。
			if (damageType == "Const") {

				m_damage = damage;
			}
			//割合ダメージを設定。
			else if (damageType == "Ratio") {

				m_damage = (target->GetStatus()->GetMaxHP() / kMaxPer) * damage;
			}
			//それ以外なら
			else {

				//警告を出力。
				nsGameWindow::MessageBoxError(L"ダメージタイプの設定が不適切です。");
			}

			//ターゲットを設定。
			m_target = target;

			//ガードできるかどうかを設定。
			m_canGuard = canGuard;
		}

		void CApplyDamageFeature::Create() {

			//ターゲットにダメージを与える。
			m_target->ApplyDamage(m_damage, m_power, m_canGuard);

			//破棄。
			Release();
		}
	}
}