#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsCamera {

		//カメラアクションクラス
		class CCameraAction : nsUtils::SNoncopyable
		{
		private:
			static CVector3 m_startAddCameraVec;		//開始時点での加算ベクトル

		public:
			void Init(nsPlayer::CPlayer* player);

			void Update();

			void Rotate(float rotateUp, float rotateRight);
		public:

			const CVector3& GetPosition()const {

				return m_position;
			}

			const CVector3& GetTargetPosition()const {
				
				return m_targetPosition;
			}

			static inline void SetStartAddCameraVec(const CVector3& vec) noexcept
			{
				m_startAddCameraVec = vec;
			}

			static inline const CVector3& GetStartAddCameraVec() noexcept
			{
				return m_startAddCameraVec;
			}

		private:
			nsPlayer::CPlayer* m_player = nullptr;			//プレイヤー
			CVector3 m_position = CVector3::Zero();			//視点
			CVector3 m_targetPosition = CVector3::Zero();	//注視点
			CVector3 m_addCameraVec = CVector3::Zero();		//注視点から視点までの加算ベクトル
		};
	}
}

