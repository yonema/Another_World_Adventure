#pragma once
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsPlayer {

		//プレイヤーの武器管理クラス
		class CPlayerWeaponManager : public nsUtils::SNoncopyable
		{
		public:
			void Init(const CModelRenderer* playerModel);

			void Release() {

				//武器情報が入っているなら。
				if (m_weapon != nullptr) {

					//武器を破棄。
					m_weapon->Release();
					m_weapon = nullptr;
				}
			}

			void Update();

			void ChangeWeapon(nsWeapon::CWeapon* weapon);

		public:
			nsWeapon::CWeapon* GetWeapon()const {

				//武器を取得。
				return m_weapon;
			}

			const nsWeapon::CWeapon* const & GetWeaponPointer() const{

				//武器の参照を取得。（変更不可）
				return m_weapon;
			}

		private:
			const CModelRenderer* m_playerModel = nullptr;	//プレイヤーモデル
			unsigned int m_weaponBaseBoneID = 0;			//武器を持たせるボーンのID

			nsWeapon::CWeapon* m_weapon = nullptr;	//武器
		};
	}
}