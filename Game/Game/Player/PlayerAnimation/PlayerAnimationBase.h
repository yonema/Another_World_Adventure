#pragma once

namespace nsAWA {

	namespace nsPlayer {

		//�G�C���A�X�錾
		enum class EnPlayerState;
		class CPlayerInput;
		namespace nsPlayerAnimation {

			enum class EnAnimName;
		}

		namespace nsPlayerAnimation {

			//�e����A�j���[�V�����̒��ۃN���X
			class CPlayerAnimationBase : nsUtils::SNoncopyable
			{
			public:
				virtual void UpdateAnimation(CModelRenderer* PlayerModel, EnPlayerState playerState) = 0;
			protected:
				bool m_isPlaying = false;		//�Đ����H
			};
		}
	}
}

