#pragma once

namespace nsAWA {

	//エイリアス宣言
	namespace nsCamera {

		class CMainCamera;
	}
	namespace nsPlayer {

		class CPlayerStatus;
	}

	namespace nsPlayer {

		//プレイヤーアクションクラス
		class CPlayerAction : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void Update(float deltaTime);

			void Move(float inputX,float inputZ);

			void Rotate();
#ifdef _DEBUG
			void UseSkill(int decreaseMPValue);	//Jobごとにスキルの中が違うので後で消す。
#endif
		private:
			const CVector3& CalculateMoveAmount(float inputX, float inputZ);

			void UpdateDeltaTime(float deltaTime) {

				//deltaTimeを更新。
				m_deltaTimeRef = deltaTime;
			}

			void UpdateForwardDirection();

			void AutoHealMP();
		public:
			const CVector3& GetPosition()const {

				//座標を取得。
				return m_position;
			}

			const CQuaternion& GetRotation()const {

				return m_rotation;
			}
		private:
			CVector3 m_position = CVector3::Zero();				//座標
			CQuaternion m_rotation = CQuaternion::Identity();	//回転
			CVector3 m_forwardDirection = CVector3::Zero();		//前方向
			CVector3 m_moveDirection = CVector3::Zero();		//移動方向
			float m_deltaTimeRef = 0.0f;						//そのフレームのdeltaTime
			float m_healMPTimer = 0.0f;							//HP自動回復用タイマー

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//メインカメラのポインタ
			CPlayerStatus* m_playerStatus = nullptr;			//プレイヤーステータスのポインタ
		};
	}
}

