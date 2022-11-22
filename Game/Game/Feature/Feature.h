#pragma once

namespace nsAWA {

	class IGameActor;

	namespace nsFeature {

		//ターゲットの参照ステータス
		enum class EnStatusRef {

			enAttack,		//物理攻撃力
			enDeffence,		//物理防御力

			enNone			//設定なし
		};

		//機能クラス
		class CFeature : nsUtils::SNoncopyable
		{
		public:
			virtual void Create() = 0;

			bool Update(float deltaTime);

			virtual float Apply(EnStatusRef statusRef) { return 1.0f; }
		public:
			void SetDurationTime(float durationTime) {

				//持続時間を設定。
				m_durationTime = durationTime;
			}

		protected:
			virtual void Execute(float deltaTime) {}

		protected:
			float m_durationTime = 0.0f;	//持続時間
		};
	}
}

