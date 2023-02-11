#include "YonemaEnginePreCompile.h"
#include "MonsterAnimationEvent.h"
#include "Monster.h"
#include "../Utils/StringManipulation.h"
#include "../CreateTrigger.h"
#include "../GameActor.h"
#include "AI/MonsterAIController.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Player/Observer/PlayerObserver.h"
#include "../GameLog/GameLog.h"

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
			else if (animationEventName == "Death") {

				Death();
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

		void CMonsterAnimationEvent::Death() {

			//プレイヤーを検索。
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			//プレイヤーに経験値を付与。
			if (player != nullptr) {

				//経験値を取得。
				player->AddExp(m_monster->GetDropExp());

				std::string getExpText = std::to_string(m_monster->GetDropExp());
				getExpText += "の経験値を獲得!";

				//経験値獲得テキストを表示。
				nsGameLog::CGameLog::GetInstance()->AddGameLog(getExpText);

				//オブザーバーに通知。
				nsPlayer::CPlayerManager::GetInstance()->NotifyObserver(nsPlayer::nsObserver::EnObserverEvent::enWin);
			}
			else {

				nsGameWindow::MessageBoxWarning(L"CMonsterAnimationEvent : playerの検索に失敗したため、戦闘後獲得処理が行えませんでした。");
			}

			//破棄処理。
			Release();
		}
	}
}