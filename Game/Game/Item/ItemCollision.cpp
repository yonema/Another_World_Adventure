#include "YonemaEnginePreCompile.h"
#include "ItemCollision.h"
#include "../Player/PlayerCollider.h"
#include "../GameActor.h"

namespace nsAWA {

	namespace nsItem {

		namespace {
			
			constexpr float kItemRigidBodyRadius = 3.0f;						//剛体の半径
			constexpr float kItemTriggerRadius = kItemRigidBodyRadius + 1.0f;	//トリガーの半径
			constexpr float kExecuteFeatureRadius = 20.0f;	//効果発動トリガーの半径
			constexpr float kItemThrowAngle = 30.0f;							//投げる角度
			constexpr float kItemThrowPower = 30.0f;							//投げる強さ

			constexpr float kExecuteFeatureTriggerTime = 3.0f;		//効果を与えるトリガーの継続時間
		}

		void CItemCollision::Init(const CVector3& position) {

			//当たり判定を初期化。
			m_rigidBody.InitAsSphere(kItemRigidBodyRadius, position,EnPhysicsAttributes::enItemRigidBody);
			m_trigger.InitAsSphere(kItemTriggerRadius, m_rigidBody.GetPosition());
			
			//効果範囲のトリガーを初期化。
			m_featureTrigger.InitAsSphere(kExecuteFeatureRadius, m_rigidBody.GetPosition());

			// TriggerEnterのコールバック関数を設定。
			m_trigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) {OnTriggerEnter(otherData); });

			// FeatureTriggerEnterのコールバック関数を設定。
			m_featureTrigger.SetOnTriggerEnterFunc(
				[&](CExtendedDataForRigidActor* otherData) {OnFeatureTriggerEnter(otherData); });

			//効果範囲トリガーは無効化。
			m_featureTrigger.Deactivate();
		}

		void CItemCollision::Throw(const CVector3& throwDirection) {

			//投げる方向を正規化。
			CVector3 finalThrowDirection = throwDirection;
			finalThrowDirection.Normalize();
			
			//投げる角度を計算。
			CQuaternion rot;
			rot.SetRotationDeg(Cross(finalThrowDirection, CVector3::AxisY()), kItemThrowAngle);

			//方向に計算された角度をつける。
			rot.Apply(finalThrowDirection);

			//力を加えて投げる。
			m_rigidBody.AddForce(finalThrowDirection * kItemThrowPower);

			//剛体から座標を取得し、トリガーに設定。
			m_trigger.SetPosition(m_rigidBody.GetPosition());
		}

		void CItemCollision::Release() {

			//各当たり判定を破棄。
			m_rigidBody.Release();
			m_trigger.Release();
			m_featureTrigger.Release();
		}

		void CItemCollision::Update(float deltaTime) {

			//何かに当たっていたら。
			if (m_isHit) {

				//時間を加算。
				m_executeTriggerTimer += deltaTime;

				//継続時間が一定時間を超えたら。
				if (m_executeTriggerTimer > kExecuteFeatureTriggerTime) {

					//終了。
					m_isEnd = true;
				}
			}

			//座標を更新。
			m_trigger.SetPosition(m_rigidBody.GetPosition());
		}

		void CItemCollision::OnTriggerEnter(CExtendedDataForRigidActor* otherData) {

			//既に何かに当たっていたら。
			if (m_isHit) {

				//早期リターン。
				return;
			}

			//自身の剛体だったら。
			if (otherData->GetPhysicsAttribute() == EnPhysicsAttributes::enItemRigidBody) {

				//早期リターン。
				return;
			}

			//投げたアイテムがプレイヤー以外の何か（自身の剛体を除く）と接触した。
			if (otherData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayer
				&& otherData->GetPhysicsAttribute() != EnPhysicsAttributes::enPlayerAttack
				)
			{
				//効果範囲トリガーを有効化。
				m_featureTrigger.Activate();
				m_featureTrigger.SetPosition(m_rigidBody.GetPosition());

				//元の判定は破棄。
				m_rigidBody.Deactivate();
				m_trigger.Deactivate();
				
				//何かに当たった。
				m_isHit = true;
			}
		}

		void CItemCollision::OnFeatureTriggerEnter(CExtendedDataForRigidActor* otherData) {

			//トリガーに入ったオブジェクトがIGameActorのコライダーかどうか調べる。
			auto rGameActorCollider = otherData->GetOwner<CGameActorCollider>();

			//IGameActorのコライダーだったら。
			if (rGameActorCollider != nullptr) {

				//リストに対象を格納。
				m_hitActorList.emplace_back(rGameActorCollider->GetGameActor());
			}
		}
	}
}