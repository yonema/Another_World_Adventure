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

		namespace {

			constexpr float kDeathEffectScale = 2.0f;	//���S�G�t�F�N�g�̃T�C�Y
		}

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

				//�o���l�l���e�L�X�g��\���B
				std::string getExpText = std::to_string(m_monster->GetDropExp());
				getExpText += "�̌o���l���l��!";
				nsGameLog::CGameLog::GetInstance()->AddGameLog(getExpText);

				//�h���b�v����\���̂���f�ރA�C�e���̃��X�g�����ɎQ�ƁB
				for (const auto& dropItemName : m_monster->GetDropItemList()) {

					//�h���b�v�m�F�B
					bool checkDrop = m_monster->CheckDrop(dropItemName);

					//�h���b�v�����B
					if (checkDrop) {

						nsPlayer::CPlayerManager::GetInstance()->GetItemManager()->AddMaterialItem(dropItemName);

						//�f�ރA�C�e���l���e�L�X�g��\���B
						std::string itemDropText = "�f�ރA�C�e�� :[";
						itemDropText += dropItemName;
						itemDropText += "] ���l��!";
						nsGameLog::CGameLog::GetInstance()->AddGameLog(itemDropText);
					}
				}
				
				//�I�u�U�[�o�[�|���������X�^�[���ƂƂ��ɒʒm�B
				nsPlayer::CPlayerManager::GetInstance()->NotifyObserver(nsPlayer::nsObserver::EnObserverEvent::enWin, m_monster->GetMonsterName());
			}
			else {

				nsGameWindow::MessageBoxWarning(L"CMonsterAnimationEvent : player�̌����Ɏ��s�������߁A�퓬��l���������s���܂���ł����B");
			}

			//���S�G�t�F�N�g�𐶐��B
			CEffectPlayer* deathEffect = NewGO<CEffectPlayer>();
			std::string effectFilePath = "Assets/Effects/Normal/enemydeath.efkefc";
			
			//�������B
			deathEffect->Init(nsUtils::GetWideStringFromString(effectFilePath).c_str());

			//�G�t�F�N�g��transform��ݒ�B
			deathEffect->SetPosition(m_monster->GetPosition());
			deathEffect->SetRotation(m_monster->GetRotation());
			deathEffect->SetScale(kDeathEffectScale);

			//�G�t�F�N�g���Đ��B
			deathEffect->Play();

			//�X�V�B
			deathEffect->Update(0.0f);

			//�j�������B
			Release();
		}
	}
}