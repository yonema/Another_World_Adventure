#pragma once
#include "../GameActor.h"
#include "MonsterStatus.h"
#include "MonsterAnimation.h"
#include "MonsterCollider.h"

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

			const CVector3& GetPosition()const override final {

				//座標を取得。（未実装）
				return CVector3::Zero();
			}

			const CVector3& GetForwardDirection()const override final {

				//前方向を取得。（未実装）
				return CVector3::Zero();
			}
		public:
			void SetState(EnMonsterState state) {

				//ステートが変わったら。
				if (m_state != state) {

					//新しいステートを設定する。
					m_state = state;

					//ステートに変更があった。
					m_isChangeState = true;
				}
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
			const char* m_name = nullptr;
			CModelRenderer* m_modelRenderer = nullptr;	//モデル
			CMonsterCollider m_collider;				//コライダー
			CMonsterStatus m_status;					//ステータス
			CMonsterAnimation m_animation;				//アニメーション
			EnMonsterState m_state = static_cast<EnMonsterState>(-1);	//ステート
			bool m_isChangeState = false;	//ステートがこのフレームで変更された？
			nsWeapon::CWeapon* m_weapon = nullptr;		//武器
			nsArmor::CArmor* m_armor = nullptr;			//防具
		};
	}
}

