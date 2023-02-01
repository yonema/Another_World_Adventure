#pragma once
#include "../Skill/ActiveSkillList.h"

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayer;

		//プレイヤー管理クラス
		class CPlayerManager : nsUtils::SNoncopyable
		{
		public:

			static CPlayerManager* GetInstance() {

				//インスタンスを生成。
				static CPlayerManager* instance = new CPlayerManager;

				//インスタンスを取得。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			bool FindPlayer();

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

			std::list<nsSkill::SActiveSkillData> GetCanUseActiveSkillList();
			
			void SetWeapon(const std::string& weaponName);

			void SetArmor(const std::string& armorName);

			void AddCanUseActiveSkill(const std::string& skillName) {

				//使用可能なアクティブスキルをリストから順に参照。
				for (const auto& activeSkillData : m_canUseActiveSkillDataList) {

					//同じ名前のスキルがあるなら。
					if (activeSkillData.name == skillName) {

						//追加する必要がないので終了。
						return;
					}
				}
				
				//名前からアクティブスキルのデータを取得。
				nsSkill::SActiveSkillData activeSkillData = nsSkill::CActiveSkillList::GetInstance()->GetActiveSkillData(skillName);

				//使用可能なアクティブスキルのデータをリストに追加。
				m_canUseActiveSkillDataList.emplace_back(activeSkillData);
			}

		private:
			void ResetActiveSkill();

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//プレイヤーのポインタ
			std::list<nsSkill::SActiveSkillData> m_canUseActiveSkillDataList;	//使用可能なアクティブスキルの名前のリスト
		};
	}
}