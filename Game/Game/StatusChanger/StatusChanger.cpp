#include "YonemaEnginePreCompile.h"
#include "StatusChanger.h"

namespace nsAWA {

	namespace nsStatusChanger {

		void CStatusChanger::UpdateAtStart(float deltaTime) {

			//�X�e�[�^�X�ω��̌��ʂ𔭓��B
			ExecuteAtStart(deltaTime);
		}

		bool CStatusChanger::UpdateAtEnd(float deltaTime) {

			//�X�e�[�^�X�ω��̌��ʂ𔭓��B
			ExecuteAtEnd(deltaTime);

			//�^�C�}�[���X�V�B
			m_durationTimer -= deltaTime;

			//���Ԃ��Ȃ��Ȃ�����B
			if (m_durationTimer < 0.0f) {

				//���g��j���B
				delete this;

				//�I�������Ƃ��Ēm�点��B
				return true;
			}

			//�I�����Ȃ����Ƃ�m�点��i�܂����ʂ��c���Ă���j�B
			return false;
		}
	}
}
