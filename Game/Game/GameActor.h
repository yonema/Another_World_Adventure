#pragma once

namespace nsAWA {

	//エイリアス宣言
	class CStatus;
	
	namespace nsFeature{

		namespace nsStatusChanger {

			class CStatusChanger;
		}
	}
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}

	//ゲームアクター
	//ステータス変化などを付与される
	class IGameActor : public IGameObject
	{
	public:

		void AddStatusChanger(nsFeature::nsStatusChanger::CStatusChanger* statusChanger);

		virtual CStatus* GetStatus() = 0;

		virtual nsWeapon::CWeapon* GetWeapon() = 0;

		virtual nsArmor::CArmor* GetArmor() = 0;

		virtual void ApplyDamage(float power, bool canGuard = true) = 0;

		virtual void HealHP(float healValue) = 0;
		virtual void HealMP(float healValue) = 0;
		virtual void HealSP(float healValue) = 0;
	protected:

		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
	private:

		void UpdateStatusChangerAtStart(float deltaTime);

		void UpdateStatusChangerAtEnd(float deltaTime);
	private:
		std::list<nsFeature::nsStatusChanger::CStatusChanger*> m_statusChanger;	//ステータスを変化させるもののリスト
	};
}

