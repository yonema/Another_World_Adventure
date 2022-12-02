#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "../Feature/FeatureManager.h"
#include "BuffDebuff.h"

namespace nsAWA {

	namespace nsFeature {

		namespace nsStatusChanger {

			void CBuffDebuff::Init(EnBuffOrDebuff buffOrDebuff,
				IGameActor* target,
				EnStatusRef statusRef,
				float value,
				float durationTime
			) {
				//情報を初期化。
				m_buffOrDebuff = buffOrDebuff;
				m_target = target;
				m_statusRef = statusRef;
				m_value = value;
				m_durationTime = durationTime;
			}

			void CBuffDebuff::Create()
			{

				//バフデバフクラスを生成。
				CBuffDebuff* buffDebuff = new CBuffDebuff;

				//バフかデバフか設定。
				buffDebuff->m_buffOrDebuff = m_buffOrDebuff;

				//参照ステータスを設定。
				buffDebuff->m_statusRef = m_statusRef;

				//増減値を設定。
				buffDebuff->m_value = m_value;

				//ターゲットを設定。
				buffDebuff->m_target = m_target;

				//持続時間を設定。
				buffDebuff->m_durationTime = m_durationTime;

				//ターゲットにもバフデバフ情報を設定。
				buffDebuff->m_target->GetFeatureManager()->AddStatusChanger(buffDebuff);
			}

			CFeature* CBuffDebuff::CreateAndReturn()
			{

				//バフデバフクラスを生成。
				CBuffDebuff* buffDebuff = new CBuffDebuff;

				//バフかデバフか設定。
				buffDebuff->m_buffOrDebuff = m_buffOrDebuff;

				//参照ステータスを設定。
				buffDebuff->m_statusRef = m_statusRef;

				//増減値を設定。
				buffDebuff->m_value = m_value;

				//ターゲットを設定。
				buffDebuff->m_target = m_target;

				//持続時間を設定。
				buffDebuff->m_durationTime = m_durationTime;

				//ターゲットにもバフデバフ情報を設定。
				buffDebuff->m_target->GetFeatureManager()->AddStatusChanger(buffDebuff);

				//生成されたバフデバフ情報をリターン。
				return buffDebuff;
			}
		}
	}
}