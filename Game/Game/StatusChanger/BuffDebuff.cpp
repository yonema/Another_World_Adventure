#include "YonemaEnginePreCompile.h"
#include "../GameActor.h"
#include "BuffDebuff.h"
#include "../Weapon/Weapon.h"

namespace nsAWA {

	namespace nsStatusChanger {

		void CBuffDebuff::Init() {

		}

		void CBuffDebuffBuilder::Create(
			EnBuffOrDebuff buffOrDebuff,
			IGameActor* target,
			EnStatusRef statusRef,
			float value,
			float durationTime
		)
		{

			//バフデバフクラスを生成。
			CBuffDebuff* buffDebuff = new CBuffDebuff;

			//バフかデバフか設定。
			buffDebuff->m_buffOrDebuff = buffOrDebuff;

			//参照ステータスを設定。
			buffDebuff->m_statusRef = statusRef;

			//増減値を設定。
			buffDebuff->m_value = value;

			//ターゲットを設定。
			buffDebuff->m_target = target;

			//持続時間を設定。
			buffDebuff->m_durationTimer = durationTime;

			//初期化処理を実行。
			buffDebuff->Init();

			//ターゲットにも状態異常を設定。
			target->AddStatusChanger(buffDebuff);
		}
	}
}