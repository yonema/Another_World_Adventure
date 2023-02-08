#pragma once
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsPlayer {

		//�v���C���[�̕���Ǘ��N���X
		class CPlayerWeaponManager : public nsUtils::SNoncopyable
		{
		public:
			void Init(const CModelRenderer* playerModel);

			void Release() {

				//�����񂪓����Ă���Ȃ�B
				if (m_weapon != nullptr) {

					//�����j���B
					m_weapon->Release();
					m_weapon = nullptr;
				}
			}

			void Update();

			void ChangeWeapon(nsWeapon::CWeapon* weapon);

		public:
			nsWeapon::CWeapon* GetWeapon()const {

				//������擾�B
				return m_weapon;
			}

			const nsWeapon::CWeapon* const & GetWeaponPointer() const{

				//����̎Q�Ƃ��擾�B�i�ύX�s�j
				return m_weapon;
			}

		private:
			const CModelRenderer* m_playerModel = nullptr;	//�v���C���[���f��
			unsigned int m_weaponBaseBoneID = 0;			//�������������{�[����ID

			nsWeapon::CWeapon* m_weapon = nullptr;	//����
		};
	}
}