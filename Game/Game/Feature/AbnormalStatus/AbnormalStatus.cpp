#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "../FeatureManager.h"
#include "AbnormalStatus.h"
#include "Poison.h"
#include "Paralysis.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			namespace {

				constexpr float kDurationTimeBase = 10.0f;	//�x�[�X�ƂȂ鎝������
			}

			void CAbnormalStatus::Init(
				EnAbnormalStatusType abnormalStatusType,
				int abnormalStatusLevel
			) {
				//����ݒ�B
				m_type = abnormalStatusType;
				m_abnormalStatusLevel = abnormalStatusLevel;
			}

			void CAbnormalStatus::Create()
			{
				m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;
				m_target->GetFeatureManager()->AddStatusChanger(this);

				return;
				//���x��0�Ȃ�B
				if (m_abnormalStatusLevel == 0) {

					//���������ɏI���B
					return;
				}

				//��Ԉُ�N���X�̐��`�𐶐��B
				CAbnormalStatus* abnormalStatus = nullptr;

				//��Ԉُ�̎�ނŐ�������N���X��ς���B
				switch (m_type) {

					//�ŁB
				case EnAbnormalStatusType::enPoison:

					//�ŃN���X�𐶐��B
					abnormalStatus = new CPoison;
					break;

					//��ჁB
				case EnAbnormalStatusType::enParalysis:

					//��ჃN���X�𐶐��B
					abnormalStatus = new CParalysis;
					break;

					//����ȊO�B
				default:
					nsGameWindow::MessageBoxError(L"��Ԉُ킪�w�肳��Ă��܂���B");
					return;
				}

				//��Ԉُ�̎�ނ�ݒ�B
				abnormalStatus->m_type = m_type;

				//�^�[�Q�b�g��ݒ�B
				abnormalStatus->m_target = m_target;

				//�������Ԃ�ݒ�B
				abnormalStatus->m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;

				//���������������s�B
				abnormalStatus->Init();

				//�^�[�Q�b�g�ɂ���Ԉُ��ݒ�B
				abnormalStatus->m_target->GetFeatureManager()->AddStatusChanger(abnormalStatus);
			}

			//CFeature* CAbnormalStatus::CreateAndReturn() {
			//
			//	//���x��0�Ȃ�B
			//	if (m_abnormalStatusLevel == 0) {
			//
			//		//���������ɏI���B
			//		nsGameWindow::MessageBoxError(L"���̊֐��ł̓��x��0��Feature�𐶐��ł��܂���B");
			//		return nullptr;
			//	}
			//
			//	//��Ԉُ�N���X�̐��`�𐶐��B
			//	CAbnormalStatus* abnormalStatus = nullptr;
			//
			//	//��Ԉُ�̎�ނŐ�������N���X��ς���B
			//	switch (m_type) {
			//
			//		//�ŁB
			//	case EnAbnormalStatusType::enPoison:
			//
			//		//�ŃN���X�𐶐��B
			//		abnormalStatus = new CPoison;
			//		break;
			//
			//		//��ჁB
			//	case EnAbnormalStatusType::enParalysis:
			//
			//		//��ჃN���X�𐶐��B
			//		abnormalStatus = new CParalysis;
			//		break;
			//
			//		//����ȊO�B
			//	default:
			//		nsGameWindow::MessageBoxError(L"��Ԉُ킪�w�肳��Ă��܂���B");
			//		return nullptr;
			//	}
			//
			//	//��Ԉُ�̎�ނ�ݒ�B
			//	abnormalStatus->m_type = m_type;
			//
			//	//�^�[�Q�b�g��ݒ�B
			//	abnormalStatus->m_target = m_target;
			//
			//	//�������Ԃ�ݒ�B
			//	abnormalStatus->m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;
			//
			//	//���������������s�B
			//	abnormalStatus->Init();
			//
			//	//�^�[�Q�b�g�ɂ���Ԉُ��ݒ�B
			//	abnormalStatus->m_target->GetFeatureManager()->AddStatusChanger(abnormalStatus);
			//
			//	//����������Ԉُ�����^�[���B
			//	return abnormalStatus;
			//}
		}
	}
}