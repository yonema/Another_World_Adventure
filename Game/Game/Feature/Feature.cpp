#include "YonemaEnginePreCompile.h"
#include "Feature.h"

namespace nsAWA {

	namespace nsFeature {

		void CFeature::Release() {

			//���g��j���B
			delete this;
		}

		bool CFeature::Update(float deltaTime) {

			//���ʂ𔭓��B
			Execute(deltaTime);

			//�^�C�}�[���X�V�B
			m_durationTime -= deltaTime;

			//�������Ԃ�0�b��؂�����B
			if (m_durationTime <= 0.0f) {

				//0�b�ɐݒ肷��B
				m_durationTime = 0.0f;
			}

			//�������Ԃ�0�b�ɂȂ�����B
			if (fabsf(m_durationTime) <= FLT_EPSILON) {

				//�I�������Ƃ��Ēm�点��B
				return true;
			}

			//�I�����Ȃ����Ƃ�m�点��i�܂����ʂ��c���Ă���j�B
			return false;
		}
	}
}