#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "BuffDebuff.h"
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsStatusChanger {

		void CBuffDebuff::Init() {

		}

		void CBuffDebuffBuilder::Init(EnBuffOrDebuff buffOrDebuff,
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

		void CBuffDebuffBuilder::Create()
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
			buffDebuff->m_durationTimer = m_durationTime;

			//初期化処理を実行。
			buffDebuff->Init();

			//ターゲットにも状態異常を設定。
			buffDebuff->m_target->AddStatusChanger(buffDebuff);
		}
	}
}