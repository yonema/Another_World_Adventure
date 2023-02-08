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
				//�������B
				Init();

				//�������Ԃ�ݒ�B
				m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;

				//�X�e�[�^�X�ύX�Ƃ��ă^�[�Q�b�g�ɒǉ��B
				m_target->GetFeatureManager()->AddStatusChanger(this);
			}
		}
	}
}