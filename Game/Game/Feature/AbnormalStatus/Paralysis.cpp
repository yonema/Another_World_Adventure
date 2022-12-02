#include "YonemaEnginePreCompile.h"
#include "Paralysis.h"
#include <random>

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
					//２種の乱数生成器を生成。ランダムデバイスからseed値を決定し、高速な乱数生成器を用いて乱数を生成する。
					std::random_device rd;
					std::mt19937_64 mt(rd());

					//しきい値を抽選。
					int canAttackPer = mt() % kPerMax;

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