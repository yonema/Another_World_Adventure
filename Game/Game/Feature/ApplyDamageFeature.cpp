#include "YonemaEnginePreCompile.h"
#include "ApplyDamageFeature.h"
#include "../GameActor.h"
#include "../Status.h"

namespace nsAWA {

	namespace nsFeature {

		namespace {
			constexpr float kMaxPer = 100.0f;	//最大％
			constexpr float kRandomDamageMax = 1.0f;	//最大火力倍率
			constexpr float kRandomDamageMin = 0.85f;	//最低火力倍率

			//理論ダメージ計算式
			constexpr float CalcDamage(
				int level,
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

			//乱数値を生成。
			nsUtils::CRandom random;
			float randomDamage = random.GetRangeFloat(kRandomDamageMin, kRandomDamageMax);

			//乱数値をダメージに乗算。
			m_damage *= randomDamage;

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

			//両者をヒットストップ。
			m_target->HitStop(0.1f);

			m_creator->HitStop(0.1f);

			//破棄。
			Release();
		}
	}
}