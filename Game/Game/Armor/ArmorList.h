#pragma once
#include "Armor.h"

namespace nsAWA {

	namespace nsArmor {

		//防具リストクラス
		class CArmorList : nsUtils::SNoncopyable
		{
		public:
			static CArmorList* GetInstance() {

				//インスタンスを生成。
				static CArmorList* instance = new CArmorList;

				//リターン。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadArmorList();

			const SArmorInfo& GetArmorData(const std::string& armorName);

		private:
			std::list<SArmorInfo> m_armorDataList;	//防具データリスト
		};
	}
}