#include "YonemaEnginePreCompile.h"
#include "Paralysis.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			namespace {

				constexpr int kCanAttackPer = 70;		//アクティブスキルが使用できる確率（％）
				constexpr int kPerMax = 100;			//最大確率（％）
			}

			void CParalysis::Init() {

				//攻撃できるかどうかの変数を初期化。
				m_canUseActiveSkill = true;
			}

			void CParalysis::Execute(float deltaTime) {

				//アクティブスキルが使用できるかを抽選。
				{
					//しきい値を抽選。
					int canAttackPer = Random()->GetRangeInt(0, kPerMax);

					//抽選された値がアクティブスキルが使用できる確率（％）より小さいなら。
					if (canAttackPer < kCanAttackPer) {

						//攻撃可能。
						m_canUseActiveSkill = true;
					}
					//アクティブスキルが使用できる確率（％）以上なら。
					else {

						//アクティブスキルが使用不可。
						m_canUseActiveSkill = false;
					}
				}
			}
		}
	}
}