#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "PassiveSkillManager.h"

namespace nsAWA {

	namespace nsSkill {

		void CPassiveSkillManager::AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill) {

			//最大可能装着数を超えてないなら。
			if (m_passiveSkill.size() < m_passiveSkillMaxNum) {

				//パッシブスキルを装着する。
				m_passiveSkill.emplace_back(passiveSkill);
			}
		}

		void CPassiveSkillManager::UpdatePassiveSkill() {

			//パッシブスキルを順に参照。
			for (const auto& passiveSkill : m_passiveSkill) {

				//更新。
				passiveSkill->Update();
			}
		}
	}
}