#include "YonemaEnginePreCompile.h"
#include "Armor.h"
#include "ArmorList.h"

namespace nsAWA {

	namespace nsArmor {

		void CArmor::Create(const SArmorInfo& armorInfo) {

			//�h�����ݒ�B
			m_sInfo = armorInfo;
		}

		void CArmor::Release() {

			//���g��j���B
			delete this;
		}

		CArmor* CArmorBuilder::CreateArmor(const std::string& armorName) {

			//�h��̐��`�𐶐��B
			CArmor* armor = new CArmor;

			//���O����h��f�[�^���擾�B
			SArmorInfo armorInfo = CArmorList::GetInstance()->GetArmorData(armorName);
			
			//�h��𐶐��B
			armor->Create(armorInfo);

			//�������ꂽ�h���Ԃ��B
			return armor;
		}
	}
}