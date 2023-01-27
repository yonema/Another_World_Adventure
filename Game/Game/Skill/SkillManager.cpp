#include "YonemaEnginePreCompile.h"
#include "SkillManager.h"
#include "../Player/Player.h"
#include "ActiveSkillList.h"
#include "ActiveSkill.h"

namespace nsAWA {

	namespace nsSkill {

		void CSkillManager::FindPlayer() {

			//プレイヤーを検索。
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			if (player != nullptr) {

				m_player = player;
			}
			else {

				nsGameWindow::MessageBoxWarning(L"CSkillManager : player が見つかりませんでした。");
			}
		}

		void CSkillManager::SetActiveSkill(int setNum, const std::string& activeSkillName) {

			if (m_player == nullptr) {

				FindPlayer();

				//プレイヤーが見つからないなら早期リターン。
				if (m_player == nullptr) { return; }
			}

			//設定番号をチェック。
			if (setNum >= CActiveSkill::m_kActiveSkillNumMax) {

				nsGameWindow::MessageBoxError(L"アクティブスキルの設定番号が規定数を超えています。");
			}

			//名前からアクティブスキルを生成。
			CActiveSkillBuilder activeSkillBuilder;
			CActiveSkill* activeSkill =  activeSkillBuilder.CreateActiveSkill(activeSkillName);

			//プレイヤーにアクティブスキルを設定。
			m_player->SetActiveSkill(setNum, activeSkill);
		}
	}
}