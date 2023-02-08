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
				m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;
				m_target->GetFeatureManager()->AddStatusChanger(this);

				return;
				//レベル0なら。
				if (m_abnormalStatusLevel == 0) {

					//生成せずに終了。
					return;
				}

				//状態異常クラスの雛形を生成。
				CAbnormalStatus* abnormalStatus = nullptr;

				//状態異常の種類で生成するクラスを変える。
				switch (m_type) {

					//毒。
				case EnAbnormalStatusType::enPoison:

					//毒クラスを生成。
					abnormalStatus = new CPoison;
					break;

					//麻痺。
				case EnAbnormalStatusType::enParalysis:

					//麻痺クラスを生成。
					abnormalStatus = new CParalysis;
					break;

					//それ以外。
				default:
					nsGameWindow::MessageBoxError(L"状態異常が指定されていません。");
					return;
				}

				//状態異常の種類を設定。
				abnormalStatus->m_type = m_type;

				//ターゲットを設定。
				abnormalStatus->m_target = m_target;

				//持続時間を設定。
				abnormalStatus->m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;

				//初期化処理を実行。
				abnormalStatus->Init();

				//ターゲットにも状態異常を設定。
				abnormalStatus->m_target->GetFeatureManager()->AddStatusChanger(abnormalStatus);
			}

			//CFeature* CAbnormalStatus::CreateAndReturn() {
			//
			//	//レベル0なら。
			//	if (m_abnormalStatusLevel == 0) {
			//
			//		//生成せずに終了。
			//		nsGameWindow::MessageBoxError(L"この関数ではレベル0のFeatureを生成できません。");
			//		return nullptr;
			//	}
			//
			//	//状態異常クラスの雛形を生成。
			//	CAbnormalStatus* abnormalStatus = nullptr;
			//
			//	//状態異常の種類で生成するクラスを変える。
			//	switch (m_type) {
			//
			//		//毒。
			//	case EnAbnormalStatusType::enPoison:
			//
			//		//毒クラスを生成。
			//		abnormalStatus = new CPoison;
			//		break;
			//
			//		//麻痺。
			//	case EnAbnormalStatusType::enParalysis:
			//
			//		//麻痺クラスを生成。
			//		abnormalStatus = new CParalysis;
			//		break;
			//
			//		//それ以外。
			//	default:
			//		nsGameWindow::MessageBoxError(L"状態異常が指定されていません。");
			//		return nullptr;
			//	}
			//
			//	//状態異常の種類を設定。
			//	abnormalStatus->m_type = m_type;
			//
			//	//ターゲットを設定。
			//	abnormalStatus->m_target = m_target;
			//
			//	//持続時間を設定。
			//	abnormalStatus->m_durationTime = m_abnormalStatusLevel * kDurationTimeBase;
			//
			//	//初期化処理を実行。
			//	abnormalStatus->Init();
			//
			//	//ターゲットにも状態異常を設定。
			//	abnormalStatus->m_target->GetFeatureManager()->AddStatusChanger(abnormalStatus);
			//
			//	//生成した状態異常をリターン。
			//	return abnormalStatus;
			//}
		}
	}
}