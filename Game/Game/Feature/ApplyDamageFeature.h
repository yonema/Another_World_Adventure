#pragma once
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		//ダメージを与える機能
		class CApplyDamageFeature : public CFeature
		{
		public:
			void Init(
				int level,
				int power,
				float attack,
				float deffence,
				IGameActor* target,
				bool canGuard
			);

			void Create()override final;
		private:
			float m_level = 0.0f;				//レベル
			float m_power = 0.0f;				//威力
			float m_attack = 0.0f;				//攻撃力
			float m_deffence = 0.0f;			//防御力
			bool m_canGuard = true;				//ガード可能？
		};
	}
}


