#pragma once

namespace nsAWA {

	//前方宣言
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

			void Release();

			bool Update(float deltaTime);

		public:
			void SetDurationTime(float durationTime) {

				//持続時間を設定。
				m_durationTime = durationTime;
			}

			void SetTarget(IGameActor* target) {

				//効果の対象を設定。
				m_target = target;
			}

			void SetCreator(IGameActor* creator) {

				//効果の生成者を設定。
				m_creator = creator;
			}

		protected:
			virtual void Execute(float deltaTime){}

		protected:
			float m_durationTime = 0.0f;	//持続時間
			IGameActor* m_target = nullptr;	//効果の対象
			IGameActor* m_creator = nullptr;//効果の生成者
		};
	}
}

