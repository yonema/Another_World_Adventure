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

			virtual CFeature* CreateAndReturn() {

				//一部の派生クラスで使用される関数のため、基底クラスのこの関数が呼ばれた場合はエラーを出力する。
				nsGameWindow::MessageBoxError(L"生成されるものがありません。");

				return nullptr;
			}

			bool Update(float deltaTime);

			virtual float Apply(EnStatusRef statusRef) { return 1.0f; }
		public:
			void SetDurationTime(float durationTime) {

				//持続時間を設定。
				m_durationTime = durationTime;
			}

			void SetTarget(IGameActor* target) {

				//効果の対象を設定。
				m_target = target;
			}

		protected:
			virtual void Execute(float deltaTime){}

		protected:
			float m_durationTime = 0.0f;	//持続時間
			IGameActor* m_target = nullptr;	//効果の対象
		};
	}
}

