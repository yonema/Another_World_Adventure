#pragma once
#include "Weapon.h"

namespace nsAWA {

	namespace nsWeapon {

		//���탊�X�g�N���X
		class CWeaponList : nsUtils::SNoncopyable
		{
		public:
			static CWeaponList* GetInstance() {

				//�C���X�^���X�𐶐��B
				static CWeaponList* instance = new CWeaponList;

				//���^�[���B
				return instance;
			}

			void DeleteInstance() {

				//�C���X�^���X��j���B
				delete GetInstance();
			}

			void LoadWeaponList();

			const SWeaponInfo& GetWeaponData(const std::string& weaponName);

		private:
			std::list<SWeaponInfo> m_weaponDataList;	//����f�[�^���X�g
		};
	}
}