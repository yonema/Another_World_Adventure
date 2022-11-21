#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "AbnormalStatus.h"
#include "Poison.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			namespace {

				constexpr float kDurationTimeBase = 10.0f;	//ベースとなる持続時間
			}

			void CAbnormalStatusBuilder::Init(
				EnAbnormalStatusType abnormalStatusType,
				IGameActor* target,
				int abnormalStatusLevel
			) {
				//情報を設定。
				m_abnormalStatusType = abnormalStatusType;
				m_target = target;
				m_abnormalStatusLevel = abnormalStatusLevel;
			}

			void CAbnormalStatusBuilder::Create()
			{
				//レベル0なら。
				if (m_abnormalStatusLevel == 0) {

					//生成せずに終了。
					return;
				}

				//状態異常クラスの雛形を生成。
				CAbnormalStatus* abnormalStatus = nullptr;

				//状態異常の種類で生成するクラスを変える。
				switch (m_abnormalStatusType) {

					//毒。
				case EnAbnormalStatusType::enPoison:

					//毒クラスを生成。
					abnormalStatus = new CPoison;
					break;
					//それ以外。
				default:
					nsGameWindow::MessageBoxError(L"状態異常が指定されていません。");
					return;
				}

				//状態異常の種類を設定。
				abnormalStatus->m_type = m_abnormalStatusType;

				//ターゲットを設定。
				abnormalStatus->m_target = m_target;

				//持続時間を設定。
				abnormalStatus->m_durationTimer = m_abnormalStatusLevel * kDurationTimeBase;

				//初期化処理を実行。
				abnormalStatus->Init();

				//ターゲットにも状態異常を設定。
				abnormalStatus->m_target->AddStatusChanger(abnormalStatus);
			}
		}
	}
}