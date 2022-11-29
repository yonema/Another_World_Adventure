#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//エイリアス宣言
		enum class EnPlayerState;
		class CPlayerInput;
		namespace nsPlayerAnimation {

			enum class EnAnimName;
		}

		namespace nsPlayerAnimation {

			//各武器アニメーションの抽象クラス
			class CPlayerAnimationBase : nsUtils::SNoncopyable
			{
			public:
				virtual void UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) = 0;
			protected:
				bool m_isPlaying = false;		//再生中？
			};
		}
	}
}

