#pragma once
#include "../Skill/ActiveSkillList.h"
#include "../Item/ItemManager.h"
#include "Observer/ObservablePlayer.h"
#include "Observer/PlayerObserver.h"

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

				//オブザーバーを破棄。
				m_observable.ReleaseObserver();

				//インスタンスを破棄。
				delete GetInstance();
			}

			void Init(CPlayer* player);

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

			void NotifyObserver(nsObserver::EnObserverEvent observerEvent,const std::string& message = "") {

				//オブザーバーに通知。
				m_observable.NotifyObserver(observerEvent,message);
			}

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

			const CVector3& GetPlayerPosition();



		public: // UI
			void ChangeFromSkillToItemUI();

			void ChangeFromItemToSkillUI();

			void MoveNextItemUI();

			void MoveBackItemUI();

			void InputEnable();

			void InputDisable();


		private:
			void ResetActiveSkill();

			void CreateObserver();

		private:
			static const std::string m_kTestFontNotFound;

		private:
			nsPlayer::CPlayer* m_player = nullptr;	//プレイヤーのポインタ
			std::list<nsSkill::SActiveSkillData> m_canUseActiveSkillDataList;	//使用可能なアクティブスキルの名前のリスト
			nsItem::CItemManager m_itemManager;		//アイテム管理クラス
			nsObserver::CObservablePlayer m_observable;				//オブザーバー監視クラス


		};
	}
}