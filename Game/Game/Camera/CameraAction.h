#pragma once

namespace nsAWA {

	namespace nsCamera {

		//カメラアクションクラス
		class CCameraAction : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void Update();

			void Rotate(float rotateUp, float rotateRight);
		public:

			const CVector3& GetPosition()const {

				return m_position;
			}

			const CVector3& GetTargetPosition()const {
				
				return m_targetPosition;
			}
		private:
			CVector3 m_position = CVector3::Zero();			//視点
			CVector3 m_targetPosition = CVector3::Zero();	//注視点
			CVector3 m_addCameraVec = CVector3::Zero();		//注視点から視点までの加算ベクトル
		};
	}
}

