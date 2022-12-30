#pragma once
#include "PlayerAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		//前方宣言
		enum class EnPlayerState;
		class CPlayerInput;

		namespace nsPlayerAnimation {

			//各武器アニメーションの抽象クラス
			class CPlayerAnimationBase : nsUtils::SNoncopyable
			{
			public:
				void Init(const std::vector<CPlayerAnimation::SAnimData>& animList) {

					//アニメーションデータを取得。
					m_animDataList = animList;
				}

				virtual void UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) = 0;

			protected:
				bool m_isPlaying = false;		//再生中？
				std::vector<CPlayerAnimation::SAnimData> m_animDataList;
			};
		}
	}
}

