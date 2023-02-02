#pragma once

namespace nsAWA {

	namespace nsMagic {

		//真っすぐ飛んでいく魔法（１つ）
		class CMagicBallOne : public IGameObject
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void Init(
				std::string name,
				const CVector3& position,
				const CVector3& moveDirection
			) {
				//データを初期化。
				m_name = name;
				SetPosition(position);
				SetMoveDirection(moveDirection);
			}

			void SetPosition(const CVector3& position) {

				//座標を設定。
				m_position = position;
			}

			void AddPosition(const CVector3& addPosition) {

				m_position += addPosition;
			}

			void SetMoveDirection(const CVector3& moveDirection) {

				//飛んでいく方向を設定。
				m_moveDirection = moveDirection;
			}

		private:
			std::string m_name = "NoName";			//エフェクトの名前
			CEffectPlayer* m_mainEffect = nullptr;	//メインのエフェクト
			CEffectPlayer* m_endEffect = nullptr;	//終了時のエフェクト
			CPhysicsTriggerObject m_trigger;	//当たり判定
			CVector3 m_position = CVector3::Zero();	//座標
			CVector3 m_moveDirection = CVector3::Zero();//飛んでいく方向
			float m_durationTime = 0.0f;		//持続時間

			std::list<std::vector<std::string>> m_featureList;		//効果のリスト
		};
	}
}