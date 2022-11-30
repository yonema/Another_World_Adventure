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
	namespace nsItem {

		class CItemManager;
	}

	//ゲームアクター
	//ステータス変化などを付与される
	class IGameActor : public IGameObject
	{
	public:
		bool Start()override final;

		void OnDestroy()override final;

		virtual bool StartSub() { return true; }
		
		virtual void OnDestroySub() {};
		
		void AddStatusChanger(nsFeature::CFeature* statusChanger);

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
	public:
		virtual CStatus* GetStatus() = 0;

		virtual nsWeapon::CWeapon* GetWeapon() = 0;

		virtual nsArmor::CArmor* GetArmor() = 0;

		nsItem::CItemManager* GetItemManager() {

			//アイテム管理クラスが生成されていないなら。
			if (m_itemManager == nullptr) {

				//警告を出す。
				nsGameWindow::MessageBoxError(L"アイテム管理クラスが生成されていません。");
			}

			//アイテムにアクセスするために、管理クラスを取得。
			return m_itemManager;
		}
	private:
		int m_passiveSkillMaxNum = 5;				//パッシブスキルの最大可能装着数
		std::list<nsFeature::CFeature*> m_feature;	//ステータスを変化させるもののリスト
		std::list<nsSkill::CPassiveSkill*> m_passiveSkill;	//パッシブスキル
		nsItem::CItemManager* m_itemManager = nullptr;		//アイテム管理
	};
}

