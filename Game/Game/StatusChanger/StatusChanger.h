#pragma once
#include "Feature.h"

namespace nsAWA {

	//エイリアス宣言
	class IGameActor;

	namespace nsStatusChanger {

		//ターゲットの参照ステータス
		enum class EnStatusRef {

			enAttack,		//物理攻撃力
			enDeffence,		//物理防御力

			enNone			//設定なし
		};

		//ステータス変化クラス
		class CStatusChanger : nsUtils::SNoncopyable
		{
		public:
			
			void UpdateAtStart(float deltaTime);

			/**
			 * @brief 戻り値ではこのステータス変化が終了したかを返す。
			*/
			bool UpdateAtEnd(float deltaTime);
		protected:
			virtual void ExecuteAtStart(float deltaTime){}
			virtual void ExecuteAtEnd(float deltaTime){}

		public:
			virtual float Apply(nsStatusChanger::EnStatusRef statusRef) { return 1.0f; }

		protected:
			float m_durationTimer = 0.0f;		//持続時間
			IGameActor* m_target = nullptr;		//効果をもたらすターゲット
		};
	}
}

