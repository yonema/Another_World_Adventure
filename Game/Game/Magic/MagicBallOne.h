#pragma once
#include "MagicBase.h"

namespace nsAWA {

	namespace nsMagic {

		//真っすぐ飛んでいく魔法（１つ）
		class CMagicBallOne : public CMagicBase
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

			void SetPosition(const CVector3& position)override final {

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
			void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

		private:
			CEffectPlayer* m_mainEffect = nullptr;	//メインのエフェクト
			CEffectPlayer* m_endEffect = nullptr;	//終了時のエフェクト
			CPhysicsTriggerObject m_trigger;	//当たり判定
			CVector3 m_position = CVector3::Zero();	//座標
			CVector3 m_moveDirection = CVector3::Zero();//飛んでいく方向
			float m_durationTime = 0.0f;		//持続時間

			
		};
	}
}