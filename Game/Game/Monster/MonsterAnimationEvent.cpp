#include "YonemaEnginePreCompile.h"
#include "MonsterAnimationEvent.h"
#include "Monster.h"
#include "../Utils/StringManipulation.h"
#include "../CreateTrigger.h"
#include "../GameActor.h"
#include "AI/MonsterAIController.h"

namespace nsAWA {

	namespace nsMonster {

		void CMonsterAnimationEvent::GetAnimationEvent(const std::string& animationEventName,
			const AnimationEventDataStr& animationEventData
		) {

			//イベントの名前から対応するメンバ関数を呼び出す。

			if (animationEventName == "CoolTimeOn") {

				CoolTimeOn();
			}
			else if (animationEventName == "CoolTimeOff") {

				CoolTimeOff();
			}
			else if (animationEventName == "CreateTrigger") {

				CreateTrigger(m_monster, animationEventData);
			}
			else if (animationEventName == "Release") {

				Release();
			}
			else {

				std::string errorMsg = "アニメーションイベントが正しく呼ばれていません。 : ";
				errorMsg += animationEventName;

				nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			}
		}

		void CMonsterAnimationEvent::CoolTimeOn() {

			//クールタイムをONに設定する。
			m_aiController->CoolTimeOn();
		}

		void CMonsterAnimationEvent::CoolTimeOff() {

			//クールタイムをOFFに設定する。
			m_aiController->CoolTimeOff();
		}

		void CMonsterAnimationEvent::CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr) {

			//トリガーを生成。
			auto trigger = NewGO<CCreateTrigger>();
			trigger->Create(
				creator,
				animEventDataStr,
				creator->GetPosition(),
				creator->GetForwardDirection()
			);
		}

		void CMonsterAnimationEvent::Release() {

			//自身を破棄。
			DeleteGO(m_monster);
		}
	}
}