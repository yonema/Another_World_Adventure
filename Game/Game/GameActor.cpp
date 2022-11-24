#include "YonemaEnginePreCompile.h"
#include "GameActor.h"
#include "Feature/feature.h"
#include "Skill/PassiveSkill.h"

namespace nsAWA {

	void IGameActor::AddStatusChanger(nsFeature::CFeature* statusChanger) {

		//ステータス変化を付与。
		m_feature.emplace_back(statusChanger);
	}

	void IGameActor::Update(float deltaTime) {

		//パッシブスキルを更新。
		UpdatePassiveSkill();

		//派生クラスを更新。
		UpdateActor(deltaTime);

		//ステータス変化を更新。
		UpdateFeature(deltaTime);
	}

	void IGameActor::UpdateFeature(float deltaTime) {

		//ステータス変化のリストのイテレータを順に参照。
		for (auto itr = m_feature.begin(); itr != m_feature.end(); ) {

			//ステータス変化の機能を更新。
			bool isDead = (*itr)->Update(deltaTime);

			//終了したか。
			if (isDead) {

				//このステータス変化を破棄。
				itr = m_feature.erase(itr);

				//破棄されたことにより、既に次のイテレータが入っているので移る処理をスキップ。
				continue;
			}

			//次のイテレータに移る。
			itr++;
		}
	}

	void IGameActor::AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill) {

		//最大可能装着数を超えてないなら。
		if (m_passiveSkill.size() < m_passiveSkillMaxNum) {

			//パッシブスキルを装着する。
			m_passiveSkill.emplace_back(passiveSkill);
		}
	}

	void IGameActor::UpdatePassiveSkill() {

		//パッシブスキルを順に参照。
		for (const auto& passiveSkill : m_passiveSkill) {

			//更新。
			passiveSkill->Update();
		}
	}
}