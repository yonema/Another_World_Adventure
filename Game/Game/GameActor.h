#pragma once

namespace nsAWA {

	//前方宣言
	class CStatus;
	class CGameActorCollider;
	
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

		virtual bool IsDeath()const = 0;

		void SetHitStop(bool flag) {

			//ヒットストップのフラグを設定。
			m_isHitStop = flag;
		}

		bool IsHitStop()const {

			//ヒットストップのフラグを取得。
			return m_isHitStop;
		}

	protected:
		void Update(float deltaTime)override final;

		virtual void UpdateActor(float deltaTime){}

	public:
		virtual CStatus* GetStatus() = 0;

		void SetPosition(const CVector3& position) {

			//座標を設定。
			m_position = position;
		}

		const CVector3& GetPosition()const {

			//座標を取得。
			return m_position;
		}

		void SetPositionOffset(const CVector3& offset) {

			//座標をオフセットを設定。
			m_positionOffset = offset;
		}

		const CVector3& GetPositionOffset()const {

			//座標のオフセットを取得。
			return m_positionOffset;
		}

		const CVector3& GetPositionAndPositionOffset()const {

			//座標をオフセット込みで取得。
			return m_position + m_positionOffset;
		}

		void SetRotation(const CQuaternion& rotation) {

			//回転を設定。
			m_rotation = rotation;
		}

		const CQuaternion& GetRotation()const {

			//回転を取得。
			return m_rotation;
		}

		void UpdateForwardDirection();

		const CVector3& GetForwardDirection()const {

			//前方向を取得。
			return m_forwardDirection;
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

		virtual CGameActorCollider* GetGameActorCollider() = 0;

		CModelRenderer* GetModelRenderer() {

			//モデルを取得。
			return m_modelRenderer;
		}
	protected:
		CModelRenderer* m_modelRenderer = nullptr;	//モデル
		CVector3 m_position = CVector3::Zero();		//座標
		CVector3 m_forwardDirection = CVector3::Zero();		//前方向
		CQuaternion m_rotation = CQuaternion::Identity();	//回転
		CVector3 m_positionOffset = CVector3::Zero();//座標のオフセット
		bool m_isHitStop = false;						//ヒットストップ中？

	private:
		nsSkill::CPassiveSkillManager* m_passiveSkillManager = nullptr;		//パッシブスキル管理
		nsFeature::CFeatureManager* m_featureManager = nullptr;		//ステータス変化管理
	};
}

