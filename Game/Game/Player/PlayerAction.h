#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsCamera {

		class CMainCamera;
	}
	namespace nsPlayer {

		class CPlayerStatus;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}
	namespace nsSkill {

		class CActiveSkill;
	}
	namespace nsItem {

		class CItemManager;
	}
	namespace nsFeature {

		class CFeatureManager;
	}

	namespace nsPlayer {

		//プレイヤーステート
		enum class EnPlayerState {								
			enIdle,			//待機
			enWalk,			//歩き
			enRun,			//ダッシュ
			enWeakAttack,	//弱攻撃
			enStrongAttack,	//強攻撃
			enStep,			//ステップ
			enUseActiveSkill,//アクティブスキル
			enDamage,		//被弾
			enDeath,		//死亡
			enGuard,		//ガード
			enUseItem,		//アイテム使用
			enStun,			//スタン

			enStateNum,		//ステート数
			enNone			//設定なし
		};

		//アクティブスキルの番号
		enum class EnActiveSkillListNumber {

			enActiveSkill_1,	//スキル1
			enActiveSkill_2,	//スキル2
			enActiveSkill_3,	//スキル3
			enActiveSkill_4,	//スキル4
			enActiveSkill_5,	//スキル5
			enActiveSkill_6,	//スキル6

			enActiveSkill_Num,	//割り当てられるアクティブスキル数
		};

		//プレイヤーアクションクラス
		class CPlayerAction : nsUtils::SNoncopyable
		{
		public:
			void Init(
				CPlayerStatus* playerStatus, 
				nsItem::CItemManager* playerItemManager,
				nsFeature::CFeatureManager* playerFeatureManager,
				nsPlayerAnimation::CPlayerAnimation* playerAnimation
			);

			void Update(float deltaTime);

			void Move(float inputX,float inputZ, float speed = 0.0f);

			void Rotate(bool slerp = true);

			void Guard();

			void UseItem();

			void AddSelectItemNum();

			void SubSelectItemNum();

			void SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill);

			void UseActiveSkill(EnActiveSkillListNumber activeSkillNum);
		private:
			const CVector3 CalculateMoveAmount(float inputX, float inputZ, float speed);

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

			const CVector3& GetForwardDirection()const {

				return m_forwardDirection;
			}
			
			void SetState(const EnPlayerState& state) {

				//ステートが変わったら。
				if (m_state != state) {

					//新しいステートを設定する。
					m_state = state;

					//ステートに変更があった。
					m_isChangeState = true;
				}
			}

			void ResetChangeState() {

				//ステートの変更状況を初期化。
				m_isChangeState = false;
			}

			void ChangeState() {

				//ステートを初期化する。
				m_state = EnPlayerState::enNone;
				m_isChangeState = true;
			}

			const EnPlayerState& GetState()const {

				return m_state;
			}

			bool IsChangeState()const {

				return m_isChangeState;
			}
		private:
			CVector3 m_position = CVector3::Zero();				//座標
			CQuaternion m_rotation = CQuaternion::Identity();	//回転
			CVector3 m_forwardDirection = CVector3::Zero();		//前方向
			CVector3 m_moveDirection = CVector3::Zero();		//移動方向
			bool m_isChangeState = false;						//ステートがこのフレームで変更された？
			EnPlayerState m_state = EnPlayerState::enNone;		//ステート
			float m_deltaTimeRef = 0.0f;						//そのフレームのdeltaTime
			nsSkill::CActiveSkill* m_activeSkill[static_cast<int>(EnActiveSkillListNumber::enActiveSkill_Num)] = { nullptr };	//アクティブスキル

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//メインカメラのポインタ
			CPlayerStatus* m_playerStatus = nullptr;			//プレイヤーステータスのポインタ
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;		//プレイヤーアニメーション
			nsItem::CItemManager* m_playerItemManager = nullptr;//プレイヤーのアイテム管理クラスのポインタ
			nsFeature::CFeatureManager* m_playerFeatureManager = nullptr;	//プレイヤーのステータス変化管理クラスのポインタ
		};
	}
}

