#pragma once

namespace nsAWA {

	//エイリアス宣言
	namespace nsCamera {

		class CMainCamera;
	}
	namespace nsPlayer {

		class CPlayerStatus;
	}
	namespace nsSkill {

		class CActiveSkill;
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
			void Init();

			void Update(float deltaTime);

			void Move(float inputX,float inputZ);

			void Rotate();

			void Guard();

			void SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill);

			void UseActiveSkill(EnActiveSkillListNumber activeSkillNum);
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
			nsSkill::CActiveSkill* m_activeSkill[static_cast<int>(EnActiveSkillListNumber::enActiveSkill_Num)] = { nullptr };	//アクティブスキル

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//メインカメラのポインタ
			CPlayerStatus* m_playerStatus = nullptr;			//プレイヤーステータスのポインタ
		};
	}
}

