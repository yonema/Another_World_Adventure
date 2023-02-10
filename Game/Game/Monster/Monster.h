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
	namespace nsUI {

		class CEnemyBattleStatusUI;
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
			enBark,				//吠える
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

			bool IsDeath()const override final {

				//HPが0以下かどうかをリターン。
				return m_status.GetHP() <= FLT_EPSILON;
			}

			void HealHP(float healValue)override final {

				//HPを回復。
				m_status.HealHP(healValue);
			}
			void HealMP(float healValue)override final {};
			void HealSP(float healValue)override final {};

			void SetForwardDirection(const CVector3& forwardDirection) {

				//前方向を設定。
				m_forwardDirection = forwardDirection;
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

			CGameActorCollider* GetGameActorCollider() {

				CGameActorCollider* col = nullptr;
				return col;
			}

			const std::string& GetMonsterName()const {

				//名前を取得。
				return m_name;
			}

			int GetDropExp()const {

				//獲得経験値量を取得。
				return m_dropExp;
			}

			const std::list<std::string>& GetDropItemList()const {

				//ドロップアイテムリストを取得。
				return m_dropItemList;
			}

			bool CheckDrop(const std::string& dropItemName);

		private:
			void CreateMonsterModel(const SMonsterInitData& monsterInfo);

		private:
			std::string m_name = "NoName";				//名前
			int m_dropExp = 0;							//獲得経験値量
			std::list<std::string> m_dropItemList;		//ドロップアイテムリスト

			CMonsterCollider m_collider;				//コライダー
			CMonsterStatus m_status;					//ステータス
			CMonsterAnimation m_animation;				//アニメーション
			nsMonsterAI::CMonsterAIController m_AIContoller;	//AIコントローラー
			EnMonsterState m_state = static_cast<EnMonsterState>(-1);	//ステート
			bool m_isChangeState = false;	//ステートがこのフレームで変更された？

			nsUI::CEnemyBattleStatusUI* m_enemyBattleStatusUI = nullptr;
		};
	}
}

