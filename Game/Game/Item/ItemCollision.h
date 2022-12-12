#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsItem {

		//アイテム剛体クラス
		class CItemCollision : nsUtils::SNoncopyable
		{
		public:
			void Init(const CVector3& position);

			void Release();

			void Throw(const CVector3& throwDirection);

			void DeactivateCollision() {

				//剛体とトリガーを非アクティブにする。
				m_rigidBody.Deactivate();
				m_trigger.Deactivate();
			}

			void Update(float deltaTime);

		private:
			void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

			void OnFeatureTriggerEnter(CExtendedDataForRigidActor* otherData);

		public:

			CVector3 GetPosition()const {

				//剛体の座標を取得。
				return m_rigidBody.GetPosition();
			}

			bool IsHit()const {

				//何かに当たったかどうか。
				return m_isHit;
			}

			bool IsEnd()const {

				//全て終了したか。
				return m_isEnd;
			}

			std::list<IGameActor*>* GetHitActorList() {

				//当たり判定に入ったアクターのリストをリターン。
				return &m_hitActorList;
			}
		private:
			CPhysicsDynamicObject m_rigidBody;				//剛体
			CPhysicsTriggerObject m_trigger;				//トリガー
			CPhysicsTriggerObject m_featureTrigger;			//効果を付与する範囲のトリガー
			bool m_isHit = false;		//何かに当たったか
			bool m_isEnd = false;		//すべて終了したか
			std::list<IGameActor*> m_hitActorList;		//当たり判定に入ったアクターのリスト
			float m_executeTriggerTimer = 0.0f;		//効果範囲トリガーのタイマー
		};
	}
}