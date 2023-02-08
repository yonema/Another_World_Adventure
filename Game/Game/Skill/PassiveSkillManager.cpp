#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "PassiveSkillManager.h"

namespace nsAWA {

	namespace nsSkill {

		void CPassiveSkillManager::Init() {

			//枠のサイズを初期化。
			m_passiveSkill.resize(m_passiveSkillMaxNum);
		}

		void CPassiveSkillManager::SetPassiveSkill(int skillNum, nsSkill::CPassiveSkill* passiveSkill) {

			//最大可能装着数を超えているなら。
			if (m_passiveSkillMaxNum <= skillNum) {

				nsGameWindow::MessageBoxError(L"CPassiveSkillManager : サイズを超えてパッシブスキルを装着しようとしています。");
			}
			else {

				//既に登録されているなら。
				if (m_passiveSkill[skillNum] != nullptr) {

					//破棄。
					m_passiveSkill[skillNum]->ReleaseFeature();
					delete m_passiveSkill[skillNum];
				}

				//新しいパッシブスキルを装着する。
				//m_passiveSkill[skillNum] = new nsSkill::CPassiveSkill;
				//m_passiveSkill[skillNum]->SetFeatureList(passiveSkill->GetFeatureList());
				//m_passiveSkill[skillNum]->SetName(passiveSkill->GetName());

				//delete passiveSkill;
				m_passiveSkill[skillNum] = passiveSkill;
			}
		}

		void CPassiveSkillManager::UpdatePassiveSkill() {

			for (const auto& passiveSkill : m_passiveSkill) {

				//パッシブスキルが登録されていなかったら。
				if (passiveSkill == nullptr) {

					//次へ。
					continue;
				}

				//更新。
				passiveSkill->Update();
			}
		}
	}
}