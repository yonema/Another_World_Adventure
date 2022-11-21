#include "YonemaEnginePreCompile.h"
#include "../../GameActor.h"
#include "AbnormalStatus.h"
#include "Poison.h"

namespace nsAWA {

	namespace nsStatusChanger {

		namespace {

			constexpr float kDurationTimeBase = 10.0f;	//ベースとなる持続時間
		}

		void CAbnormalStatusBuilder::Create(
			EnAbnormalStatusType abnormalStatusType,
			IGameActor* target,
			int abnormalStatusLevel
		)
		{
			//レベル0なら。
			if (abnormalStatusLevel == 0) {

				//生成せずに終了。
				return;
			}

			//状態異常クラスの雛形を生成。
			CAbnormalStatus* abnormalStatus = nullptr;

			//状態異常の種類で生成するクラスを変える。
			switch (abnormalStatusType) {

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
			abnormalStatus->m_type = abnormalStatusType;

			//ターゲットを設定。
			abnormalStatus->m_target = target;

			//持続時間を設定。
			abnormalStatus->m_durationTimer = abnormalStatusLevel * kDurationTimeBase;

			//初期化処理を実行。
			abnormalStatus->Init();

			//ターゲットにも状態異常を設定。
			target->AddStatusChanger(abnormalStatus);
		}
	}
}