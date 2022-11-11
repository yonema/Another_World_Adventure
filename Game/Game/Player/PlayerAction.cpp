#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount_Walk = 20.0f;				//歩き状態の移動量
			constexpr const float kMoveAmount_Dash = 30.0f;				//ダッシュ状態の移動量
			constexpr const float kRotationSlerpRate = 9.375f;			//回転の補間率
			constexpr const float kAutoHealMPTimeInterval = 0.1f;		//MP自動回復間隔
			constexpr const int kAutoHealMPValue = 1;					//MP自動回復量
			constexpr const float kAutoHealSPTimeInterval = 0.1f;		//SP自動回復間隔
			constexpr const int kAutoHealSPValue = 1;					//SP自動回復量
			constexpr const float kAutoHealGuardGaugeInterval = 0.1f;	//ガードゲージの値自動回復間隔
			constexpr const int kAutoHealGuardGaugeValueAmount = 1;		//ガードゲージの値自動回復量
			constexpr const int kDashSPDamage = 2;						//ダッシュによるSP減少量
			constexpr const float kDashSPTimeInterval = 0.1f;			//ダッシュによるSP減少間隔
		}

		void CPlayerAction::Init() {

			//カメラを検索。
			m_mainCamera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

			//プレイヤーを検索。
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);

			//プレイヤーのステータスを保持。
			m_playerStatus = player->GetStatus();
		}

		void CPlayerAction::Update(float deltaTime) {

			//deltaTimeを更新(各関数で必要になるため)。
			UpdateDeltaTime(deltaTime);

			//前方向を更新。
			UpdateForwardDirection();

			//MPを自動回復。
			AutoHealMP();

			//SPを自動回復。
			AutoHealSP();

			//ガード中以外か。
			if (m_state != EnPlayerState::enGuard) {
				
				//ガードゲージの値を自動回復。
				AutoHealGuardGaugeValue();
			}
		}

		void CPlayerAction::Move(float inputX, float inputZ) {

			//ダッシュ状態か。
			if (m_state == EnPlayerState::enDash) {

				//ダッシュにより、SPを減少させる。
				DamageSPDash();
			}

			//移動量を計算。
			CVector3 moveAmount = CalculateMoveAmount(inputX, inputZ);

			//移動方向を計算。
			m_moveDirection = moveAmount;
			//正規化。
			m_moveDirection.Normalize();

			//移動。
			m_position += moveAmount;
		}

		void CPlayerAction::Rotate() {

			//入力による回転角度を求める。
			float angle = atan2(-m_moveDirection.x, m_moveDirection.z);

			//回転情報を設定。
			CQuaternion rotSource = CQuaternion::Identity();
			rotSource.SetRotation(CVector3::AxisY(), -angle);

			//回転速度の補間率を求める。
			float rotationSlerpRate = kRotationSlerpRate * m_deltaTimeRef;

			//線形補間。
			m_rotation.Slerp(rotationSlerpRate, m_rotation, rotSource);
		}

		void CPlayerAction::Guard() {

			//ガード状態に設定。
			m_state = EnPlayerState::enGuard;
		}

#ifdef _DEBUG
		void CPlayerAction::StrongAttack() {

			//強攻撃を繰り出す。
			//...

			//SPを消費する。
			m_playerStatus->DamageSP(30);
		}
#endif

		const CVector3& CPlayerAction::CalculateMoveAmount(float inputX, float inputZ) {

			//カメラの前方向、右方向を取得。
			auto cameraForward = m_mainCamera->GetForwardDirection();
			auto cameraRight = m_mainCamera->GetRightDirection();

			//不要な成分を初期化して正規化。
			cameraForward.y = 0.0f;
			cameraForward.Normalize();
			cameraRight.y = 0.0f;
			cameraRight.Normalize();

			//移動速度を初期化。
			float moveAmountf = 0.0f;

			//ダッシュ状態か。
			if (m_state == EnPlayerState::enDash) {

				//走る速度を代入。
				moveAmountf = kMoveAmount_Dash;
			}
			else {
				//歩く速度を代入。
				moveAmountf = kMoveAmount_Walk;
			}

			//移動量を計算。
			CVector3 moveAmount = CVector3::Zero();
			moveAmount += cameraForward * inputZ * moveAmountf * m_deltaTimeRef;
			moveAmount += cameraRight * inputX * moveAmountf * m_deltaTimeRef;

			//リターン。
			return moveAmount;
		}

		void CPlayerAction::UpdateForwardDirection() {

			//回転行列を計算。
			auto mRot = CMatrix::Identity();
			mRot.MakeRotationFromQuaternion(m_rotation);

			//前方向を設定。
			m_forwardDirection.x = mRot.m_fMat[2][0];
			m_forwardDirection.y = mRot.m_fMat[2][1];
			m_forwardDirection.z = mRot.m_fMat[2][2];

			//正規化。
			m_forwardDirection.Normalize();
		}

		void CPlayerAction::AutoHealMP() {

			//タイマーを加算。
			m_healMPTimer += m_deltaTimeRef;

			//タイマーが一定間隔幅を超えたら。
			if (m_healMPTimer >= kAutoHealMPTimeInterval) {

				//MPを自動回復。
				m_playerStatus->HealMP(kAutoHealMPValue);

				//タイマーを減算。
				m_healMPTimer -= kAutoHealMPTimeInterval;
			}
		}

		void CPlayerAction::AutoHealSP() {

			//タイマーを加算。
			m_healSPTimer += m_deltaTimeRef;

			//タイマーが一定間隔幅を超えたら。
			if (m_healSPTimer >= kAutoHealSPTimeInterval) {

				//SPを自動回復。
				m_playerStatus->HealSP(kAutoHealSPValue);

				//タイマーを減算。
				m_healSPTimer -= kAutoHealSPTimeInterval;
			}
		}

		void CPlayerAction::DamageSPDash() {

			//タイマーを加算。
			m_dashSPTimer += m_deltaTimeRef;

			//タイマーが一定間隔幅を超えたら。
			if (m_dashSPTimer >= kDashSPTimeInterval) {

				//SPを減少。
				m_playerStatus->DamageSP(kDashSPDamage);

				//タイマーを減算。
				m_dashSPTimer -= kDashSPTimeInterval;
			}
		}

		void CPlayerAction::AutoHealGuardGaugeValue() {

			//タイマーを加算。
			m_healGuardGaugeValueTimer += m_deltaTimeRef;

			//タイマーが一定間隔幅を超えたら。
			if (m_healGuardGaugeValueTimer >= kAutoHealGuardGaugeInterval) {

				//ガードゲージの値を自動回復。
				m_playerStatus->HealGuardGaugeValue(kAutoHealGuardGaugeValueAmount);

				//タイマーを減算。
				m_healGuardGaugeValueTimer -= kAutoHealGuardGaugeInterval;
			}
		}
	}
}
