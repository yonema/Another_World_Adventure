#include "YonemaEnginePreCompile.h"
#include "AbnormalStatus.h"
#include "Poison.h"

namespace nsAWA {

	namespace nsAbnormalStatus {

		namespace {

			constexpr float kDurationTimeBase = 10.0f;	//�x�[�X�ƂȂ鎝������
		}

		bool CAbnormalStatus::Update(float deltaTime) {

			//�^�C�}�[���X�V�B
			m_durationTimer -= deltaTime;

			//���Ԃ��Ȃ��Ȃ�����B
			if (m_durationTimer < 0.0f) {

				//���g��j���B
				delete this;
				
				//�I�������Ƃ��Ēm�点��B
				return true;
			}

			//��Ԉُ�̌��ʂ𔭓��B
			Execute(deltaTime);

			//�I�����Ȃ����Ƃ�m�点��i�܂����ʂ��c���Ă���j�B
			return false;
		}

		void CAbnormalStatusBuilder::Create(
			EnAbnormalStatusType abnormalStatusType,
			IGameActor* target,
			int abnormalStatusLevel
		)
		{
			//���x��0�Ȃ�B
			if (abnormalStatusLevel == 0) {

				//���������ɏI���B
				return;
			}

			//��Ԉُ�N���X�̐��`�𐶐��B
			CAbnormalStatus* abnormalStatus = nullptr;

			//��Ԉُ�̎�ނŐ�������N���X��ς���B
			switch (abnormalStatusType) {

			//�ŁB
			case EnAbnormalStatusType::enPoison:

				//�ŃN���X�𐶐��B
				abnormalStatus = new CPoison;
				break;
			//����ȊO�B
			default:
				nsGameWindow::MessageBoxError(L"��Ԉُ킪�w�肳��Ă��܂���B");
			}

			//��Ԉُ�̎�ނ�ݒ�B
			abnormalStatus->m_type = abnormalStatusType;

			//�^�[�Q�b�g��ݒ�B
			abnormalStatus->m_target = target;

			//�������Ԃ�ݒ�B
			abnormalStatus->m_durationTimer = abnormalStatusLevel * kDurationTimeBase;

			//���������������s�B
			abnormalStatus->Init();

			//�^�[�Q�b�g�ɂ���Ԉُ��ݒ�B
			target->AddAbnormalStatus(abnormalStatus);
		}
	}
}