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

		private:
			void OnTriggerEnter(CExtendedDataForRigidActor* otherData);

		private:
			CEffectPlayer* m_mainEffect = nullptr;	//メインのエフェクト
			CPhysicsTriggerObject m_trigger;	//当たり判定
			
			
			float m_durationTime = 0.0f;		//持続時間

			
		};
	}
}