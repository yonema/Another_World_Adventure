#pragma once

namespace nsAWA {

	namespace nsCamera {

		//メインカメラクラス
		class CMainCamera : public IGameObject
		{
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		private:
			CVector3 m_position = CVector3::Zero();			//視点
			CVector3 m_target = CVector3::Zero();			//注視点
			CVector3 m_addCameraVec = CVector3::Zero();		//注視点から視点までの加算ベクトル
		};
	}
}

