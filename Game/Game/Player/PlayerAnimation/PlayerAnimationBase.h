#pragma once
#include "PlayerAnimation.h"

namespace nsAWA {

	namespace nsPlayer {

		//�O���錾
		enum class EnPlayerState;
		class CPlayerInput;

		namespace nsPlayerAnimation {

			//�e����A�j���[�V�����̒��ۃN���X
			class CPlayerAnimationBase : nsUtils::SNoncopyable
			{
			public:
				void Init(const std::vector<CPlayerAnimation::SAnimData>& animList) {

					//�A�j���[�V�����f�[�^���擾�B
					m_animDataList = animList;
				}

				virtual void UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) = 0;

			protected:
				bool m_isPlaying = false;		//�Đ����H
				std::vector<CPlayerAnimation::SAnimData> m_animDataList;
			};
		}
	}
}

