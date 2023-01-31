#include "YonemaEnginePreCompile.h"
#include "Armor.h"
#include "ArmorList.h"

namespace nsAWA {

	namespace nsArmor {

		void CArmor::Create(const SArmorInfo& armorInfo) {

			//防具情報を設定。
			m_sInfo = armorInfo;
		}

		void CArmor::Release() {

			//自身を破棄。
			delete this;
		}

		CArmor* CArmorBuilder::CreateArmor(const std::string& armorName) {

			//防具の雛形を生成。
			CArmor* armor = new CArmor;

			//名前から防具データを取得。
			SArmorInfo armorInfo = CArmorList::GetInstance()->GetArmorData(armorName);
			
			//防具を生成。
			armor->Create(armorInfo);

			//生成された防具を返す。
			return armor;
		}
	}
}