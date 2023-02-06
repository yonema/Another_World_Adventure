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

		private:
			CEffectPlayer* m_effect = nullptr;	//エフェクト
		};
	}
}