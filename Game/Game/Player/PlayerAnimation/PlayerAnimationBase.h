#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//エイリアス宣言
		enum class EnPlayerState;
		namespace nsPlayerAnimation {

			enum class EnAnimName;
		}

		namespace nsPlayerAnimation {

			//各武器アニメーションの抽象クラス
			class CPlayerAnimationBase : nsUtils::SNoncopyable
			{
			public:
				virtual void UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) = 0;
			};
		}
	}
}

