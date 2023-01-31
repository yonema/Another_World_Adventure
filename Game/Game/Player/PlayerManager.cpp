#include "YonemaEnginePreCompile.h"
#include "PlayerManager.h"
#include "Player.h"
#include "../Skill/ActiveSkillList.h"
#include "../Skill/ActiveSkill.h"
#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"

namespace nsAWA {

	namespace nsPlayer {

		bool CPlayerManager::FindPlayer() {

			//既にプレイヤーが見つかっているなら。
			if (m_player != nullptr) {

				//成功。
				return true;
			}

			//プレイヤーを検索。
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			if (player != nullptr) {

				//プレイヤーを発見。
				m_player = player;

				//成功。
				return true;
			}
			else {

				//プレイヤーが見つからなかった。
				return false;
			}
		}

		void CPlayerManager::SetActiveSkill(int setNum, const std::string& activeSkillName) {

			//設定番号をチェック。
			if (setNum >= nsSkill::CActiveSkill::m_kActiveSkillNumMax) {

				nsGameWindow::MessageBoxError(L"アクティブスキルの設定番号が規定数を超えています。");
			}

			//名前からアクティブスキルを生成。
			nsSkill::CActiveSkillBuilder activeSkillBuilder;
			nsSkill::CActiveSkill* activeSkill =  activeSkillBuilder.CreateActiveSkill(activeSkillName);

			//プレイヤーにアクティブスキルを設定。
			m_player->SetActiveSkill(setNum, activeSkill);
		}

		void CPlayerManager::SetWeapon(const std::string& weaponName) {

			//武器構築クラスを生成。
			nsWeapon::CWeaponBuilder weaponBuilder;

			//武器を生成。
			nsWeapon::CWeapon* weapon = weaponBuilder.CreateWeapon(weaponName);

			//武器を設定。
			m_player->SetWeapon(weapon);
		}

		void CPlayerManager::SetArmor(const std::string& armorName) {

			//防具構築クラスを生成。
			nsArmor::CArmorBuilder armorBuilder;

			//防具を生成。
			nsArmor::CArmor* armor = armorBuilder.CreateArmor(armorName);

			//防具を設定。
			m_player->SetArmor(armor);
		}
	}
}