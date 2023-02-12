#pragma once
#include "../Skill/ActiveSkillList.h"
#include "../Item/ItemManager.h"

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

			void Init(IGameActor* player) {

				//アイテム管理クラスを初期化。
				m_itemManager.Init(player);
			}

			bool FindPlayer();

			void SetPlayer(CPlayer* player);

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

			void SetPassiveSkill(int setNum, const std::string& passiveSkillName);

			std::list<nsSkill::SActiveSkillData> GetCanUseActiveSkillList();

			std::list<nsSkill::SActiveSkillData> GetCanUseActiveSkillListAll() {

				//全ての使用可能なアクティブスキルのリストをリターン。
				return m_canUseActiveSkillDataList;
			}
			
			void SetWeapon(const std::string& weaponName);

			void SetArmor(const std::string& armorName);



		public:
			const std::string& GetActiveSkillName(const int skillNum);

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

			nsItem::CItemManager* GetItemManager() {

				//アイテム管理クラスをリターン。
				return &m_itemManager;
			}



		public: // UI
			void ChangeFromSkillToItemUI();

			void ChangeFromItemToSkillUI();

			void MoveNextItemUI();

			void MoveBackItemUI();

		private:
			void ResetActiveSkill();

		private:
			static const std::string m_kTestFontNotFound;

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//プレイヤーのポインタ
			std::list<nsSkill::SActiveSkillData> m_canUseActiveSkillDataList;	//使用可能なアクティブスキルの名前のリスト
			nsItem::CItemManager m_itemManager;		//アイテム管理クラス
		};
	}
}