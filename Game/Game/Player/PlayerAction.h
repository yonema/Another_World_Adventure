#pragma once

namespace nsAWA {

	//エイリアス宣言
	namespace nsCamera {

		class CMainCamera;
	}

	namespace nsPlayer {

		//プレイヤーアクションクラス
		class CPlayerAction
		{
		public:
			void Init();

			void Move(float inputX,float inputZ);

		public:
			void UpdateDeltaTime(float deltaTime) {

				//deltaTimeを更新。
				m_deltaTimeRef = deltaTime;
			}

			const CVector3& GetPosition()const {

				//座標を取得。
				return m_position;
			}
		private:
			CVector3 m_position = CVector3::Zero();	//座標
			float m_deltaTimeRef = 0.0f;			//そのフレームのdeltaTime	
			nsCamera::CMainCamera* m_mainCamera = nullptr;		//メインカメラのポインタ
		};
	}
}

