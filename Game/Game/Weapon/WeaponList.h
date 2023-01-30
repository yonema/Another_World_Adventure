#pragma once
#include "Weapon.h"

namespace nsAWA {

	namespace nsWeapon {

		//武器リストクラス
		class CWeaponList : nsUtils::SNoncopyable
		{
		public:
			static CWeaponList* GetInstance() {

				//インスタンスを生成。
				static CWeaponList* instance = new CWeaponList;

				//リターン。
				return instance;
			}

			void DeleteInstance() {

				//インスタンスを破棄。
				delete GetInstance();
			}

			void LoadWeaponList();

			const SWeaponInfo& GetWeaponData(const std::string& weaponName);

		private:
			std::list<SWeaponInfo> m_weaponDataList;	//武器データリスト
		};
	}
}