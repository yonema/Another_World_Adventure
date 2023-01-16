#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"
#include "MonsterAnimation.h"
#include "MonsterCollider.h"
#include "AI/MonsterAIController.h"

namespace nsAWA {

	//前方宣言
	namespace nsWeapon {

		class CWeapon;
	}
	namespace nsArmor {

		class CArmor;
	}
	namespace nsMonster {

		enum class EnMonsterList;
		enum class EnMonsterState;
		struct SMonsterInitData;
	}

	namespace nsMonster {

		//モンスターのステート
		enum class EnMonsterState {

			enIdle,				//待機
			enWalk,				//歩く
			enRun,				//走る
			enWeakAttack,		//弱攻撃
			enStrongAttack,		//強攻撃
			enDamage,			//被弾
			enDeath,			//死亡

			enNum,		//ステートの数
			enNone = -1	//設定なし
		};

		//モンスタークラス
		class CMonster : public IGameActor
		{
		public:
			static const char* const m_kObjName_Monster;		//モンスタークラスの名前

		public:
			bool StartSub()override final;

			void OnDestroySub()override final;

			void UpdateActor(float deltaTime)override final;

			void Create(const SMonsterInitData& monsterInfo);

			void ApplyDamage(float damage, float power = 0.0f, bool canGuard = true)override final;

			void HealHP(float healValue)override final {};
			void HealMP(float healValue)override final {};
			void HealSP(float healValue)override final {};

			

			void SetPosition(const CVector3& position) {

				//座標を設定。
				m_position = position;
			}

			const CVector3& GetPosition()const override final {

				//座標を取得。
				return m_position;
			}

			void SetRotation(const CQuaternion& rotation) {

				//回転を設定。
				m_rotation = rotation;
			}

			const CQuaternion& GetRotation()const {

				//回転を取得。
				return m_rotation;
			}

			void SetForwardDirection(const CVector3& forwardDirection) {

				//前方向を設定。
				m_forwardDirection = forwardDirection;
			}

			const CVector3& GetForwardDirection()const override final {

				//前方向を取得。
				return m_forwardDirection;
			}
		public:
			void SetState(const EnMonsterState& state) {

				//ステートが変わったら。
				if (m_state != state) {

					//新しいステートを設定する。
					m_state = state;

					//ステートに変更があった。
					m_isChangeState = true;
				}
			}

			const EnMonsterState& GetState()const {

				//ステートを取得。
				return m_state;
			}

			CStatus* GetStatus()override final;

			nsWeapon::CWeapon* GetWeapon()override final;

			nsArmor::CArmor* GetArmor()override final;

			CGameActorCollider* GetGameActorCollider() {

				CGameActorCollider* col = nullptr;
				return col;
			}

		private:
			void CreateMonsterModel(const SMonsterInitData& monsterInfo);

		private:
			const char* m_name = nullptr;				//名前
			CModelRenderer* m_modelRenderer = nullptr;	//モデル

			CVector3 m_position = CVector3::Zero();		//座標
			CQuaternion m_rotation = CQuaternion::Identity();	//回転
			CVector3 m_forwardDirection = CVector3::Zero();		//前方向

			CMonsterCollider m_collider;				//コライダー
			CMonsterStatus m_status;					//ステータス
			CMonsterAnimation m_animation;				//アニメーション
			nsMonsterAI::CMonsterAIController m_AIContoller;	//AIコントローラー
			EnMonsterState m_state = static_cast<EnMonsterState>(-1);	//ステート
			bool m_isChangeState = false;	//ステートがこのフレームで変更された？
			nsWeapon::CWeapon* m_weapon = nullptr;		//武器
			nsArmor::CArmor* m_armor = nullptr;			//防具
		};
	}
}

