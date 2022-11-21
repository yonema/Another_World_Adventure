#pragma once
#include "StatusChanger.h"

namespace nsAWA {

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
		float m_level = 0;					//レベル
		float m_power = 0;					//威力
		float m_attack = 0.0f;				//攻撃力
		float m_deffence = 0.0f;			//防御力
		IGameActor* m_target = nullptr;		//ターゲット
		bool m_canGuard = true;				//ガード可能？
	};
}


