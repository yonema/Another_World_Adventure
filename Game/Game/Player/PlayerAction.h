#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//プレイヤーアクションクラス
		class CPlayerAction
		{
		public:
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
		};
	}
}

