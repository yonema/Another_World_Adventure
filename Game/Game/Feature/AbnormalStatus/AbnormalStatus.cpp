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

				constexpr float kDurationTimeBase = 10.0f;	//ベースとなる持続時間
			}

			void CAbnormalStatus::Init(
				EnAbnormalStatusType abnormalStatusType,
				int abnormalStatusLevel
			) {
				//情報を設定。
				m_type = abnormalStatusType;
				m_abnormalStatusLevel = abnormalStatusLevel;
			}

			void CAbnormalStatus::Create()
			{
				//初期化。
				Init();

				//持続時間を設定。
				m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;

				//ステータス変更としてターゲットに追加。
				m_target->GetFeatureManager()->AddStatusChanger(this);
			}
		}
	}
}