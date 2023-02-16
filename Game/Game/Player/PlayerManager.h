#pragma once
#include "../Skill/ActiveSkillList.h"
#include "../Item/ItemManager.h"
#include "Observer/ObservablePlayer.h"
#include "Observer/PlayerObserver.h"

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;
		

		//�v���C���[�Ǘ��N���X
		class CPlayerManager : nsUtils::SNoncopyable
		{
		public:
			static CPlayerManager* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CPlayerManager* instance = new CPlayerManager;

				//�C���X�^���X���擾�B
				return instance;
			}

			void DeleteInstance() {

				//�I�u�U�[�o�[��j���B
				m_observable.ReleaseObserver();

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void Init(CPlayer* player);

			bool FindPlayer();

			void SetPlayer(CPlayer* player);

			void SetActiveSkill(int setNum, const std::string& activeSkillName);

			void SetPassiveSkill(int setNum, const std::string& passiveSkillName);

			std::list<nsSkill::SActiveSkillData> GetCanUseActiveSkillList();

			std::list<nsSkill::SActiveSkillData> GetCanUseActiveSkillListAll() {

				//�S�Ă̎g�p�\�ȃA�N�e�B�u�X�L���̃��X�g�����^�[���B
				return m_canUseActiveSkillDataList;
			}
			
			void SetWeapon(const std::string& weaponName);

			void SetArmor(const std::string& armorName);

			void NotifyObserver(nsObserver::EnObserverEvent observerEvent,const std::string& message = "") {

				//�I�u�U�[�o�[�ɒʒm�B
				m_observable.NotifyObserver(observerEvent,message);
			}

		public:
			const std::string& GetActiveSkillName(const int skillNum);

			void AddCanUseActiveSkill(const std::string& skillName) {

				//�g�p�\�ȃA�N�e�B�u�X�L�������X�g���珇�ɎQ�ƁB
				for (const auto& activeSkillData : m_canUseActiveSkillDataList) {

					//�������O�̃X�L��������Ȃ�B
					if (activeSkillData.name == skillName) {

						//�ǉ�����K�v���Ȃ��̂ŏI���B
						return;
					}
				}
				
				//���O����A�N�e�B�u�X�L���̃f�[�^���擾�B
				nsSkill::SActiveSkillData activeSkillData = nsSkill::CActiveSkillList::GetInstance()->GetActiveSkillData(skillName);

				//�g�p�\�ȃA�N�e�B�u�X�L���̃f�[�^�����X�g�ɒǉ��B
				m_canUseActiveSkillDataList.emplace_back(activeSkillData);
			}

			nsItem::CItemManager* GetItemManager() {

				//�A�C�e���Ǘ��N���X�����^�[���B
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
			nsPlayer::CPlayer* m_player = nullptr;	//�v���C���[�̃|�C���^
			std::list<nsSkill::SActiveSkillData> m_canUseActiveSkillDataList;	//�g�p�\�ȃA�N�e�B�u�X�L���̖��O�̃��X�g
			nsItem::CItemManager m_itemManager;		//�A�C�e���Ǘ��N���X
			nsObserver::CObservablePlayer m_observable;				//�I�u�U�[�o�[�Ď��N���X


		};
	}
}