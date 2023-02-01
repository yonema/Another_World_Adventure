#pragma once
#include "Armor.h"

namespace nsAWA {

	namespace nsArmor {

		//�h��X�g�N���X
		class CArmorList : nsUtils::SNoncopyable
		{
		public:
			static CArmorList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CArmorList* instance = new CArmorList;

				//���^�[���B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadArmorList();

			const SArmorInfo& GetArmorData(const std::string& armorName);

		private:
			std::list<SArmorInfo> m_armorDataList;	//�h��f�[�^���X�g
		};
	}
}