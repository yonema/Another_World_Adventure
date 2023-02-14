#pragma once
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsPlayer {

		class CPlayerAction;

		//�v���C���[�̕���Ǘ��N���X
		class CPlayerWeaponManager : public nsUtils::SNoncopyable
		{
		public:
			void Init(const CModelRenderer* playerModel, const CPlayerAction* action);

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

			void CreateEffect(const std::string& effectFilePath);

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

			void UpdateEffect();

		private:
			const CModelRenderer* m_playerModel = nullptr;	//�v���C���[���f��
			const CPlayerAction* m_playerAction = nullptr;	//�v���C���[�A�N�V����
			unsigned int m_weaponBaseBoneID = 0;			//�������������{�[����ID

			nsWeapon::CWeapon* m_weapon = nullptr;	//����
			CEffectPlayer* m_mainEffect = nullptr;	//�G�t�F�N�g
		};
	}
}