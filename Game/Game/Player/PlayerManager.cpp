#include "YonemaEnginePreCompile.h"
#include "PlayerManager.h"
#include "Player.h"
#include "../Skill/ActiveSkillList.h"
#include "../Skill/ActiveSkill.h"
#include "../Skill/PassiveSkillList.h"
#include "../Skill/PassiveSkill.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Feature/FeatureBuilder.h"
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

		void CPlayerManager::SetPlayer(CPlayer* player) {

			//プレイヤーを設定。
			m_player = player;

			//アイテム管理クラスのターゲットを設定。
			m_itemManager.SetTatget(player);
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

		void CPlayerManager::SetPassiveSkill(int setNum, const std::string& passiveSkillName) {

			//設定番号をチェック。
			if (setNum >= m_player->GetPassiveSkillManager()->GetPassiveSkillMaxNum()) {

				nsGameWindow::MessageBoxError(L"パッシブスキルの設定番号が規定数を超えています。");
			}

			//名前からパッシブスキルを生成。
			nsSkill::CPassiveSkillBuilder passiveSkillBuilder;
			nsSkill::CPassiveSkill* passiveSkill = passiveSkillBuilder.CreatePassiveSkill(passiveSkillName);

			//リストから効果を生成。
			nsFeature::CFeatureBuilder featureBuilder;
			featureBuilder.CreateFeature(m_player, m_player, passiveSkill->GetFeatureListStr(), passiveSkill->GetFeatureList());

			//プレイヤーにパッシブスキルを設定。
			m_player->GetPassiveSkillManager()->SetPassiveSkill(setNum, passiveSkill);
		}

		std::list<nsSkill::SActiveSkillData> CPlayerManager::GetCanUseActiveSkillList() {

			//使用可能なアクティブスキルのリストを定義。
			std::list<nsSkill::SActiveSkillData> canUseActiveSkillList;

			//武器種を取得。
			nsWeapon::EnWeaponType type = m_player->GetWeapon()->GetWeaponType();
			std::string typeName = "NoTypeName";

			switch (type) {

			case nsWeapon::EnWeaponType::enSword:
				typeName = "Sword";
				break;
			case nsWeapon::EnWeaponType::enAxe:
				typeName = "Axe";
				break;
			case nsWeapon::EnWeaponType::enWand:
				typeName = "Wand";
				break;
			}

			for (const auto& activeSkill : m_canUseActiveSkillDataList) {

				//武器種とタイプがあっているか、魔法スキルなら。
				if (activeSkill.type == typeName || activeSkill.type == "Magic") {

					//使えるアクティブスキルとして設定。
					canUseActiveSkillList.emplace_back(activeSkill);
				}
			}

			//使えるアクティブスキルのデータをリターン。
			return canUseActiveSkillList;
		}

		void CPlayerManager::ResetActiveSkill() {

			//武器種を取得。
			nsWeapon::EnWeaponType weaponType = m_player->GetWeapon()->GetWeaponType();

			//武器種からタイプを定義。
			nsSkill::CActiveSkill::EnActiveSkillType activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enNone;

			switch (weaponType) {

			case nsWeapon::EnWeaponType::enSword:
				activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enSword;
				break;
			case nsWeapon::EnWeaponType::enAxe:
				activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enAxe;
				break;
			case nsWeapon::EnWeaponType::enWand:
				activeSkillType = nsSkill::CActiveSkill::EnActiveSkillType::enWand;
				break;
			}

			//アクティブスキルを順に参照。
			for (int activeSkillNum = 0; activeSkillNum < nsSkill::CActiveSkill::m_kActiveSkillNumMax; activeSkillNum++) {

				//アクティブスキルを取得。
				nsSkill::CActiveSkill* activeSkill = m_player->GetActiveSkill(activeSkillNum);

				//アクティブスキルが設定されていなかったら。
				if (activeSkill == nullptr) {

					//次へ。
					continue;
				}

				//設定中のアクティブスキルが魔法スキルじゃなく、
				//武器種と一致していなかったら。
				if (activeSkill->GetType() != nsSkill::CActiveSkill::EnActiveSkillType::enMagic
					&& activeSkillType != activeSkill->GetType()) {

					//そのアクティブスキルを外す。
					m_player->SetActiveSkill(activeSkillNum, nullptr);
				}
			}
		}

		void CPlayerManager::SetWeapon(const std::string& weaponName) {

			//武器構築クラスを生成。
			nsWeapon::CWeaponBuilder weaponBuilder;

			//武器を生成。
			nsWeapon::CWeapon* weapon = weaponBuilder.CreateWeapon(weaponName);

			//武器を設定。
			m_player->SetWeapon(weapon);

			//アクティブスキルの設定を更新。
			ResetActiveSkill();
		}

		void CPlayerManager::SetArmor(const std::string& armorName) {

			//防具構築クラスを生成。
			nsArmor::CArmorBuilder armorBuilder;

			//防具を生成。
			nsArmor::CArmor* armor = armorBuilder.CreateArmor(armorName);

			//防具を設定。
			m_player->SetArmor(armor);
		}

		const std::string& CPlayerManager::GetActiveSkillName(const int skillNam)
		{
			if (false == FindPlayer()) {
				nsGameWindow::MessageBoxWarning(L"CPlayerManager : player が見つかりませんでした。");
			}

			return m_player->GetActiveSkill(skillNam)->GetName();
		}
	}
}