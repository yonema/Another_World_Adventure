#pragma once

namespace nsAWA {

	namespace nsBackGround {

		//バックグラウンドクラス
		class CBackGround : public IGameObject
		{
		public:
			static const char* const m_kObjName_BackGround;		//バックグラウンドクラスの名前
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;
		private:
			CPhysicsStaticObject m_physicsStaticObject;		//当たり判定
			CModelRenderer* m_stageModel = nullptr;			//地面モデル
		};
	}
}