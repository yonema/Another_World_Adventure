#pragma once

namespace nsAWA {

	//エイリアス宣言
	class CStatus;
	
	namespace nsFeature{

		class CFeature;
	}
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}
	namespace nsSkill {

		class CPassiveSkill;
	}

	//ゲームアクター
	//ステータス変化などを付与される
	class IGameActor : public IGameObject
	{
	public:

		void AddStatusChanger(nsFeature::CFeature* statusChanger);

		virtual CStatus* GetStatus() = 0;

		virtual nsWeapon::CWeapon* GetWeapon() = 0;

		virtual nsArmor::CArmor* GetArmor() = 0;

		virtual void ApplyDamage(float power, bool canGuard = true) = 0;

		virtual void HealHP(float healValue) = 0;
		virtual void HealMP(float healValue) = 0;
		virtual void HealSP(float healValue) = 0;

		void AddPassiveSkill(nsSkill::CPassiveSkill* passiveSkill);
	protected:

		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
	private:

		void UpdateFeature(float deltaTime);

		void UpdatePassiveSkill();
	private:
		int m_passiveSkillMaxNum = 5;				//パッシブスキルの最大可能装着数
		std::list<nsFeature::CFeature*> m_feature;	//ステータスを変化させるもののリスト
		std::list<nsSkill::CPassiveSkill*> m_passiveSkill;	//パッシブスキル
	};
}

