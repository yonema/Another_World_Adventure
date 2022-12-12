#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsItem {

		class CItem;
	}

	namespace nsItem {

		//�A�C�e�����
		struct SItemInfo {

			std::string name = "";								//���O
			std::string itemType = "";							//�A�C�e���̃^�C�v
			std::list<std::vector<std::string>> featureList;	//���ʂ̏��̃��X�g
		};

		//�Q�[�����ł̂�����A�C�e���̃��X�g
		class CAllItemList : nsUtils::SNoncopyable
		{
		public:
			static CAllItemList* GetInstance() {

				//�C���X�^���X�����^�[���B
				static CAllItemList* instance = new CAllItemList;

				return instance;
			}

			static void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadAllItemList();

			bool IsFoundName(std::string itemName);

		public:
			const SItemInfo& GetItemInfo(std::string itemName);

		private:
			void CreateItemInfo(std::list<std::vector<std::string>> itemInfo);

			void ClearItemInfoBase(SItemInfo& itemInfoBase);

		private:
			std::list<SItemInfo> m_allItemList;		//�S�ẴA�C�e���̏��
			SItemInfo m_itemList;					//��̃A�C�e�����
		};

		//�A�C�e�������N���X
		class CItemBuilder : nsUtils::SNoncopyable {

		public:
			CItem* CreateItemBase(std::string itemName);
		};
	}
}