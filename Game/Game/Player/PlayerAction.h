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

		//プレイヤーステート
		enum class EnPlayerState {								
			enIdle,			//待機
			enWalk,			//歩き
			enDash,			//ダッシュ
			enGuard,		//ガード

			enStateNum		//ステート数
		};

		//プレイヤーアクションクラス
		class CPlayerAction : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void Update(float deltaTime);

			void Move(float inputX,float inputZ);

			void Rotate();

			void Guard();
#ifdef _DEBUG
			//強攻撃。ジョブごとに違うので後で消す。
			void StrongAttack();
#endif
		private:
			const CVector3 CalculateMoveAmount(float inputX, float inputZ);

			void UpdateDeltaTime(float deltaTime) {

				//deltaTimeを更新。
				m_deltaTimeRef = deltaTime;
			}

			void UpdateForwardDirection();

			void AutoHealMP();

			void AutoHealSP();

			void DamageSPDash();

			void AutoHealGuardGaugeValue();
		public:
			const CVector3& GetPosition()const {

				//座標を取得。
				return m_position;
			}

			const CQuaternion& GetRotation()const {

				return m_rotation;
			}
			
			void SetState(const EnPlayerState& state) {

				m_state = state;
			}
			const EnPlayerState& GetState()const {

				return m_state;
			}
		private:
			CVector3 m_position = CVector3::Zero();				//座標
			CQuaternion m_rotation = CQuaternion::Identity();	//回転
			CVector3 m_forwardDirection = CVector3::Zero();		//前方向
			CVector3 m_moveDirection = CVector3::Zero();		//移動方向
			EnPlayerState m_state = EnPlayerState::enIdle;		//ステート
			float m_deltaTimeRef = 0.0f;						//そのフレームのdeltaTime
			float m_healMPTimer = 0.0f;							//MP自動回復用タイマー
			float m_healSPTimer = 0.0f;							//SP自動回復用タイマー
			float m_healGuardGaugeValueTimer = 0.0f;			//ガードゲージの値自動回復用タイマー
			float m_dashSPTimer = 0.0f;							//ダッシュによるSPダメージタイマー

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//メインカメラのポインタ
			CPlayerStatus* m_playerStatus = nullptr;			//プレイヤーステータスのポインタ
		};
	}
}

