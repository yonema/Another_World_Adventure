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

namespace nsAWA {

	namespace nsMonster {

		void CMonsterAnimationEvent::GetAnimationEvent(const std::string& animationEventName,
			const AnimationEventDataStr& animationEventData
		) {

			//�C�x���g�̖��O����Ή����郁���o�֐����Ăяo���B

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

				std::string errorMsg = "�A�j���[�V�����C�x���g���������Ă΂�Ă��܂���B : ";
				errorMsg += animationEventName;

				nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
			}
		}

		void CMonsterAnimationEvent::CoolTimeOn() {

			//�N�[���^�C����ON�ɐݒ肷��B
			m_aiController->CoolTimeOn();
		}

		void CMonsterAnimationEvent::CoolTimeOff() {

			//�N�[���^�C����OFF�ɐݒ肷��B
			m_aiController->CoolTimeOff();
		}

		void CMonsterAnimationEvent::CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr) {

			//�g���K�[�𐶐��B
			auto trigger = NewGO<CCreateTrigger>();
			trigger->Create(
				creator,
				animEventDataStr,
				creator->GetPosition(),
				creator->GetForwardDirection()
			);
		}

		void CMonsterAnimationEvent::Release() {

			//���g��j���B
			DeleteGO(m_monster);
		}

		void CMonsterAnimationEvent::Death() {

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

			//�v���C���[�Ɍo���l��t�^�B
			if (player != nullptr) {

				//�o���l���擾�B
				player->AddExp(m_monster->GetDropExp());

				//�I�u�U�[�o�[�ɒʒm�B
				nsPlayer::CPlayerManager::GetInstance()->NotifyObserver(nsPlayer::nsObserver::EnObserverEvent::enWin);
			}
			else {

				nsGameWindow::MessageBoxWarning(L"CMonsterAnimationEvent : player�̌����Ɏ��s�������߁A�퓬��l���������s���܂���ł����B");
			}

			//�j�������B
			Release();
		}
	}
}