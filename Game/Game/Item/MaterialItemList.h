#pragma once
namespace nsAWA {

	namespace nsItem {

		//�f�ރA�C�e�����
		struct SMaterialItemInfo {

			std::string name = "NoName";	//���O
			std::string rank = "NoRank";	//���A�x
		};

		//�f�ރA�C�e�����X�g
		class CMaterialItemList : nsUtils::SNoncopyable
		{
		public:
			static CMaterialItemList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CMaterialItemList* instance = new CMaterialItemList;

				//�C���X�^���X�����^�[���B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}
			const SMaterialItemInfo& GetMaterialItemInfo(const std::string& itemName);

			void LoadMaterialItemList();

			bool IsFoundName(std::string itemName);

		private:
			std::list<SMaterialItemInfo> m_materialItemList;	//�f�ރA�C�e�����X�g
		};
	}
}

