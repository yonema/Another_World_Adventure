#pragma once
#include "MagicBase.h"

namespace nsAWA {

	namespace nsMagic {

		//プレイヤーに魔法をかけるクラス
		class CMagicToPlayer : public CMagicBase
		{
		public:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		private:
			CEffectPlayer* m_effect = nullptr;	//エフェクト
			float m_effectDurationTime = 0.0f;	//エフェクトの持続時間
		};
	}
}