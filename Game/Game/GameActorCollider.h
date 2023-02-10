#pragma once

namespace nsAWA {

	class IGameActor;

	//ゲームアクターの当たり判定クラス
	class CGameActorCollider : nsUtils::SNoncopyable
	{
	public:
		void Init(IGameActor* gameActor) {

			//親のゲームアクターを設定。
			m_gameActor = gameActor;

			//当たり判定を生成。
			CreateCollider();
		}
		virtual void CreateCollider() = 0;

		void Release();

	public:

		IGameActor* GetGameActor()const {

			//親のゲームアクターを取得。
			return m_gameActor;
		}

		const CPhysicsTriggerObject* GetTrigger()const {

			//トリガーを取得。
			return &m_trigger;
		}
	private:
		CPhysicsDynamicObject m_rigidBody;				//剛体
		CPhysicsTriggerObject m_trigger;				//トリガー
	protected:
		IGameActor* m_gameActor = nullptr;				//親のゲームアクター
	};
}