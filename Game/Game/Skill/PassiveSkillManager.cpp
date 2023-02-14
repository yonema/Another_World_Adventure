#include "YonemaEnginePreCompile.h"
#include "PassiveSkill.h"
#include "PassiveSkillManager.h"

namespace nsAWA {

	namespace nsSkill {

		void CPassiveSkillManager::Init() {


		}

		void CPassiveSkillManager::Release() {

			//パッシブスキルを破棄。
			for (auto itr = m_passiveSkill.begin(); itr != m_passiveSkill.end(); ) {

				if ((*itr) != nullptr) {
					//破棄。
					delete (*itr);
				}
				itr = m_passiveSkill.erase(itr);

				continue;
			}
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

				//新たなパッシブスキルを設定。
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