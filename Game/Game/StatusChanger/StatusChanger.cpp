#include "YonemaEnginePreCompile.h"
#include "StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		bool CStatusChanger::Update(float deltaTime) {

			//�^�C�}�[���X�V�B
			m_durationTimer -= deltaTime;

			//���Ԃ��Ȃ��Ȃ�����B
			if (m_durationTimer < 0.0f) {

				//���g��j���B
				delete this;

				//�I�������Ƃ��Ēm�点��B
				return true;
			}

			//�X�e�[�^�X�ω��̌��ʂ𔭓��B
			Execute(deltaTime);

			//�I�����Ȃ����Ƃ�m�点��i�܂����ʂ��c���Ă���j�B
			return false;
		}

	}
}
