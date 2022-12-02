#pragma once

namespace nsAWA {

	//前方宣言
	class CStatus;
	
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}
	namespace nsFeature{

		class CFeatureManager;
	}
	
	namespace nsSkill {

		class CPassiveSkillManager;
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

		virtual void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true) = 0;

		virtual void HealHP(float healValue) = 0;
		virtual void HealMP(float healValue) = 0;
		virtual void HealSP(float healValue) = 0;

	protected:
		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}
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

		nsSkill::CPassiveSkillManager* GetPassiveSkillManager() {

			//パッシブスキル管理クラスが生成されていないなら。
			if (m_passiveSkillManager == nullptr) {

				//警告を出す。
				nsGameWindow::MessageBoxError(L"パッシブスキル管理クラスが生成されていません。");
			}

			//パッシブスキルにアクセスするために、管理クラスを取得。
			return m_passiveSkillManager;
		}

		nsFeature::CFeatureManager* GetFeatureManager() {

			//ステータス変化管理クラスが生成されていないなら。
			if (m_featureManager == nullptr) {

				//警告を出す。
				nsGameWindow::MessageBoxError(L"ステータス変化管理クラスが生成されていません。");
			}

			//ステータス変化のリストにアクセスするために、管理クラスを取得。
			return m_featureManager;
		}
	private:
		nsItem::CItemManager* m_itemManager = nullptr;		//アイテム管理
		nsSkill::CPassiveSkillManager* m_passiveSkillManager = nullptr;		//パッシブスキル管理
		nsFeature::CFeatureManager* m_featureManager = nullptr;		//ステータス変化管理
	};
}

