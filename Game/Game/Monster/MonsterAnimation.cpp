#include "YonemaEnginePreCompile.h"
#include "MonsterAnimation.h"
#include "MonsterList.h"

namespace nsAWA {

	namespace nsMonster {

		void CMonsterAnimation::Init(CModelRenderer* monsterModel, EnMonsterList monster) {

			//モンスターのモデルのポインタを受け取る。
			m_monsterModel = monsterModel;

			//何のモンスターなのかの情報を受け取る。
			m_monster = monster;
		}

		void CMonsterAnimation::Update(bool changeState, EnMonsterState state) {

			//ステートに変更があったら。
			if (changeState) {

				//ステートに対応するアニメーションを再生。
				PlayAnimation(state);
			}
		}

		void CMonsterAnimation::PlayAnimation(EnMonsterState state) {

			//ステートから対応アニメーションのindexを取得。
			int animationIndex = GetAnimationIndex(m_monster, state);

			//対応するアニメーションがないなら。
			if (animationIndex == -1) {

				//再生できないので早期リターン。
				return;
			}
			else {

				//対応するアニメーションを再生。（まだ再生スピードとループフラグが設定できない。未実装）
				m_monsterModel->PlayAnimation(animationIndex, 1.0f, true);
			}
		}
	}
}