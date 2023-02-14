#include "YonemaEnginePreCompile.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"
#include "../Skill/ActiveSkill.h"
#include "PlayerManager.h"
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
			CVector3& position,
			CQuaternion& rotation,
			CPlayerStatus* playerStatus, 
			nsFeature::CFeatureManager* playerFeatureManager,
			nsPlayerAnimation::CPlayerAnimation* playerAnimation
		) {
			//座標を取得。
			m_position = &position;

			//回転を取得。
			m_rotation = &rotation;

			//カメラを検索。
			m_mainCamera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

			//プレイヤーのステータスを保持。
			m_playerStatus = playerStatus;

			//プレイヤーのステータス変化管理クラスを保持。
			m_playerFeatureManager = playerFeatureManager;

			//プレイヤーアニメーションのポインタを取得。
			m_playerAnimation = playerAnimation;
		}

		void CPlayerAction::Release() {

			//アクティブスキルを破棄。
			for (auto& activeSkill : m_activeSkill) {

				if (activeSkill != nullptr) {

					delete activeSkill;
					activeSkill = nullptr;
				}
			}
		}

		void CPlayerAction::Update(float deltaTime) {

			//deltaTimeを更新(各関数で必要になるため)。
			UpdateDeltaTime(deltaTime);

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

		void CPlayerAction::Move(float inputX, float inputZ, float speed) {

			//ダッシュ状態か。
			if (m_state == EnPlayerState::enRun) {

				//ダッシュにより、SPを減少させる。
				DamageSPDash();
			}

			//移動量を計算。
			CVector3 moveAmount = CalculateMoveAmount(inputX, inputZ, speed);

			//移動方向を計算。
			m_moveDirection = moveAmount;
			//正規化。
			m_moveDirection.Normalize();

			//移動。
			*m_position += moveAmount;
		}

		void CPlayerAction::Rotate(bool slerp) {

			//入力による回転角度を求める。
			float angle = atan2(-m_moveDirection.x, m_moveDirection.z);

			//回転情報を設定。
			CQuaternion rotSource = CQuaternion::Identity();
			rotSource.SetRotation(CVector3::AxisY(), -angle);

			//補間する？
			if (slerp) {
				//回転速度の補間率を求める。
				float rotationSlerpRate = kRotationSlerpRate * m_deltaTimeRef;

				//線形補間。
				(*m_rotation).Slerp(rotationSlerpRate, *m_rotation, rotSource);
			}
			else {

				//そのまま設定。
				*m_rotation = rotSource;
			}
		}

		void CPlayerAction::Guard() {

			//ガード状態に設定。
			m_state = EnPlayerState::enGuard;
		}

		void CPlayerAction::UseItem() {

			//アイテム管理クラスを取得。
			auto itemManager = CPlayerManager::GetInstance()->GetItemManager();

			//アイテムを持っていたら。
			if (itemManager->HasItem()) {
			
				//選択中のアイテムを使用。
				itemManager->UseItem();
			
				//アイテム使用状態にする。
				SetState(EnPlayerState::enUseItem);
			}
		}

		void CPlayerAction::SetActiveSkill(int activeSkillNum, nsSkill::CActiveSkill* activeSkill) {

			//現在登録しているアクティブスキルを破棄。
			if (m_activeSkill[activeSkillNum] != nullptr) {

				delete m_activeSkill[activeSkillNum];
				m_activeSkill[activeSkillNum] = nullptr;
			}

			//新たにアクティブスキルを設定。
			m_activeSkill[activeSkillNum] = activeSkill;
		}

		nsSkill::CActiveSkill* CPlayerAction::GetActiveSkill(int activeSkillNum)const {

			//範囲外の番号指定をしていたら。
			if (activeSkillNum > nsSkill::CActiveSkill::m_kActiveSkillNumMax) {

				//エラー出力。
				nsGameWindow::MessageBoxError(L"範囲外のアクティブスキル番号です。");
				std::abort();
			}

			//アクティブスキルを取得。
			return m_activeSkill[activeSkillNum];
		}

		void CPlayerAction::UseActiveSkill(EnActiveSkillListNumber activeSkillNum) {

			//消費MPを取得。
			float useMP = m_activeSkill[static_cast<int>(activeSkillNum)]->GetUseMP();

			//MPが足りないなら。
			if (m_playerStatus->GetMP() < useMP) {

				//早期リターン。
				return;
			}

			//MPを消費。
			m_playerStatus->DamageMP(useMP);

			//スキルを実行。
			m_activeSkill[static_cast<int>(activeSkillNum)]->Execute();

			//アクティブスキルが使用できない状態だったら。
			if (!m_playerFeatureManager->CanUseActiveSkill()) {

				//専用エフェクトを再生。（未実装）

				//終了。
				return;
			}

			//アクティブスキルのアニメーションを予約。
			m_playerAnimation->ReserveActiveSkillAnimation(m_activeSkill[static_cast<int>(activeSkillNum)]);

			//アクティブスキル使用状態に。
			SetState(EnPlayerState::enUseActiveSkill);
		}

		const CVector3 CPlayerAction::CalculateMoveAmount(float inputX, float inputZ, float speed) {

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
			if (m_state == EnPlayerState::enRun) {

				//走る速度を代入。
				moveAmountf = kMoveAmount_Walk * kMoveAmount_Dash;
			}
			else if (speed > FLT_EPSILON) {

				moveAmountf = speed;
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
