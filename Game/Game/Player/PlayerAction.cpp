#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"
#include "../Skill/ActiveSkill.h"
#include "../Item/ItemManager.h"
#include "../Feature/FeatureManager.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount_Walk = 40.0f;				//歩き状態の移動量
			constexpr const float kMoveAmount_Dash = 1.3f;				//ダッシュ状態の移動倍率
			constexpr const float kRotationSlerpRate = 9.375f;			//回転の補間率
			constexpr const float kAutoHealMPValue = 10.0f;				//MP自動回復量（％/s）
			constexpr const float kAutoHealSPValue = 10.0f;				//SP自動回復量（％/s）
			constexpr const float kAutoHealGuardGaugeValue = 20.0f;		//ガードゲージの値自動回復量（％/s）
			constexpr const float kDashSPDamage = 10.0f;				//ダッシュによるSP減少量（％/s）
			constexpr const float kGuardGauge100 = 100.0f;				//ガードゲージの最大値（100と定義する）
			constexpr const float kPerMax = 100.0f;						//最大％
		}

		void CPlayerAction::Init(
			CPlayerStatus* playerStatus, 
			nsItem::CItemManager* playerItemManager,
			nsFeature::CFeatureManager* playerFeatureManager
		) {

			//カメラを検索。
			m_mainCamera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

			//プレイヤーのステータスを保持。
			m_playerStatus = playerStatus;

			//プレイヤーのアイテム管理クラスを保持。
			m_playerItemManager = playerItemManager;

			//プレイヤーのステータス変化管理クラスを保持。
			m_playerFeatureManager = playerFeatureManager;
		}

		void CPlayerAction::Update(float deltaTime) {

			//ステートの変更状況を初期化。
			m_isChangeState = false;

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

			//スタン中かつガードゲージが100になったら（最大値をとらないのはバフデバフで最大値が変化する可能性があるため）
			if (m_state == EnPlayerState::enStun
				&& fabsf(m_playerStatus->GetGuardGaugeValue() - kGuardGauge100) < FLT_EPSILON
				) {

				//スタンを解除し、待機状態にする。
				SetState(EnPlayerState::enIdle);
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

		void CPlayerAction::UseItem() {

			//アイテムを持っていたら。
			if (m_playerItemManager->HasItem()) {

				//選択中のアイテムを使用。
				m_playerItemManager->UseItem();

				//アイテム使用状態にする。
				SetState(EnPlayerState::enUseItem);
			}
		}

		void CPlayerAction::AddSelectItemNum() {

			//次のアイテムを選択。
			m_playerItemManager->AddSelectItemNum();
		}

		void CPlayerAction::SubSelectItemNum() {

			//前のアイテムを選択。
			m_playerItemManager->SubSelectItemNum();
		}

		void CPlayerAction::SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill) {

			//アクティブスキルを設定。
			m_activeSkill[static_cast<int>(activeSkillNum)] = activeSkill;
		}

		void CPlayerAction::UseActiveSkill(EnActiveSkillListNumber activeSkillNum) {

			//消費MPを取得。
			float useMP = m_activeSkill[static_cast<int>(activeSkillNum)]->GetUseMP();

			//MPが足りているなら。
			if (m_playerStatus->GetMP() >= useMP) {

				//MPを消費。
				m_playerStatus->DamageMP(useMP);

				//アクティブスキルが使用できない状態だったら。
				if (!m_playerFeatureManager->CanUseActiveSkill()) {

					//専用エフェクトを再生。（未実装）

					//終了。
					return;
				}

				//アクティブスキルを使用。
				m_activeSkill[static_cast<int>(activeSkillNum)]->Execute();
			}
		}

		const CVector3 CPlayerAction::CalculateMoveAmount(float inputX, float inputZ) {

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
				moveAmountf = kMoveAmount_Walk * kMoveAmount_Dash;
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

			//回復量を計算。
			float healValue = m_playerStatus->GetMaxMP() * (kAutoHealMPValue / kPerMax) * m_deltaTimeRef;

			//MPを自動回復。
			m_playerStatus->HealMP(healValue);
		}

		void CPlayerAction::AutoHealSP() {

			//回復量を計算。
			float healValue = m_playerStatus->GetMaxSP() * (kAutoHealSPValue / kPerMax) * m_deltaTimeRef;

			//SPを自動回復。
			m_playerStatus->HealSP(healValue);
		}

		void CPlayerAction::DamageSPDash() {

			//消費量を計算。
			float damageValue = m_playerStatus->GetMaxSP() * (kDashSPDamage / kPerMax) * m_deltaTimeRef;

			//SPを消費。
			m_playerStatus->DamageSP(damageValue);
		}

		void CPlayerAction::AutoHealGuardGaugeValue() {

			//回復量を計算。
			float healValue = m_playerStatus->GetMaxGuardGaugeValue() * (kAutoHealGuardGaugeValue / kPerMax) * m_deltaTimeRef;

			//ガードゲージを自動回復。
			m_playerStatus->HealGuardGaugeValue(healValue);
		}
	}
}
