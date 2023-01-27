#include "YonemaEnginePreCompile.h"
#include "PlayerSkillChanger.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Skill/ActiveSkill.h"

namespace nsAWA {

	namespace nsPlayer {

		void CPlayerSkillChanger::Init() {

			//プレイヤーを検索。
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			//プレイヤーアクションクラスを取得。
			m_playerAction = &(player->GetPlayerAction());
		}

		void CPlayerSkillChanger::SetActiveSkill(int skillNum, const std::string& skillName) {

			//アクティブスキルを生成。
			nsSkill::CActiveSkill* activeSkill = CreateActiveSkill(skillName);

			//アクティブスキルを設定。
			m_playerAction->SetActiveSkill(skillNum, activeSkill);
		}

		nsSkill::CActiveSkill* CPlayerSkillChanger::CreateActiveSkill(const std::string skillName) {

			std::string name = "NoName";
			int useMP = 0;

			//リストからアクティブスキルを取得（未実装）。

			

			//情報を元にアクティブスキルを生成。
			nsSkill::CActiveSkill* activeSkill = new nsSkill::CActiveSkill;
			activeSkill->SetName(name);
			activeSkill->SetUseMP(useMP);

			return activeSkill;
		}
	}
}