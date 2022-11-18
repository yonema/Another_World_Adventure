#include "YonemaEnginePreCompile.h"
#include "AbnormalStatus.h"
#include "Poison.h"

namespace nsAWA {

	namespace nsAbnormalStatus {

		namespace {

			constexpr float kDurationTimeBase = 10.0f;	//ベースとなる持続時間
		}

		bool CAbnormalStatus::Update(float deltaTime) {

			//タイマーを更新。
			m_durationTimer -= deltaTime;

			//時間がなくなったら。
			if (m_durationTimer < 0.0f) {

				//自身を破棄。
				delete this;
				
				//終了したとして知らせる。
				return true;
			}

			//状態異常の効果を発動。
			Execute(deltaTime);

			//終了しないことを知らせる（まだ効果が残っている）。
			return false;
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
			target->AddAbnormalStatus(abnormalStatus);
		}
	}
}