#include "YonemaEnginePreCompile.h"
#include "PlayerAnimationEvent.h"
#include "../../GameActor.h"
#include "../PlayerInput.h"
#include "../PlayerAction.h"
#include "PlayerAnimation.h"
#include "../Utils/StringManipulation.h"
#include "../../CreateTrigger.h"
#include "../../Skill/ActiveSkill.h"
#include "../../Magic/MagicList.h"
#include "../../Magic/MagicBase.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace nsPlayerAnimation {

			namespace {

				constexpr float kMoveSpeed = 60.0f;		//�A�N�e�B�u�X�L���ɂ��ړ����x
				constexpr const float kCanPlayerMoveInput = 0.001f;	//�ړ����͂����肳���Œ�l
			}

			void CPlayerAnimationEvent::Update() {

				//�C�x���g�ɂ���ē����t���O�������Ă���Ȃ�B
				if (m_isMoving) {

					//�ړ�
					Move();
				}
			}

			void CPlayerAnimationEvent::CoolTimeOn() {

				//���͕s�ɐݒ�B
				m_playerInput->InputDisable();

				//�N�[���^�C��ON�B
				m_playerInput->CoolTimeOn();
			}

			void CPlayerAnimationEvent::CoolTimeOff() {

				//���͉\�ɐݒ�B
				m_playerInput->InputEnable();

				//�N�[���^�C��OFF�B
				m_playerInput->CoolTimeOff();

				//�X�e�[�g������������B
				m_playerInput->ChangeState();
			}

			void CPlayerAnimationEvent::InputEnable() {

				//���͉\�ɐݒ�B
				m_playerInput->InputEnable();
			}

			void CPlayerAnimationEvent::CreateTrigger(IGameActor* creator, const AnimationEventDataStr& animEventDataStr) {

				auto trigger = NewGO<CCreateTrigger>();
				trigger->Create(
					creator,
					animEventDataStr,
					m_player->GetPosition(),
					m_player->GetForwardDirection()
				);
			}

			void CPlayerAnimationEvent::MoveStart() {

				//���͂��󂯎��B
				m_playerMoveInput.x = Input()->GetVirtualAxis(EnAxisMapping::enRight);
				m_playerMoveInput.z = Input()->GetVirtualAxis(EnAxisMapping::enForward);

				//�ړ��t���O��ON�B
				m_isMoving = true;
			}

			void CPlayerAnimationEvent::MoveEnd() {

				//���͏����������B
				m_playerMoveInput.x = 0.0f;
				m_playerMoveInput.z = 0.0f;

				//�ړ��t���O��OFF�B
				m_isMoving = false;
			}

			void CPlayerAnimationEvent::Move() {

				//�ǂ̕����ɓ��͂���Ă������B
				if (std::fabsf(m_playerMoveInput.x) > kCanPlayerMoveInput
					|| std::fabsf(m_playerMoveInput.z) > kCanPlayerMoveInput
				){
					//��]�B
					m_playerAction->Rotate(
						false	//��ԂȂ�
					);

					//�ړ��B
					m_playerAction->Move(m_playerMoveInput.x, m_playerMoveInput.z, kMoveSpeed);
				}
				else {

					//�O�������擾�B
					m_playerMoveInput = m_player->GetForwardDirection();

					//�ړ��B
					m_playerAction->Move(m_playerMoveInput.x, m_playerMoveInput.z, kMoveSpeed);
				}
			}

			void CPlayerAnimationEvent::CreateMagic() {

				//���ݎg�p���̖��@�X�L���̖��O���擾����B
				std::string magicName = m_playerAnimation->GetReserveActiveSkillInfo()->GetName();

				//���@�𐶐��B
				nsMagic::CMagicBuilder magicBuilder;
				auto magic = magicBuilder.CreateMagic(magicName);

				//�����҂�ݒ�B
				magic->SetOwner(m_player);

				//���W��ݒ�B
				magic->SetPosition(m_player->GetPosition());

				//�ˏo������ݒ�B
				magic->SetMoveDirection(m_player->GetForwardDirection());
			}

			void CPlayerAnimationEvent::GetAnimationEvent(const std::string& animationEventName,
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

					CreateTrigger(m_player,animationEventData);
				}
				else if (animationEventName == "MoveStart") {

					MoveStart();
				}
				else if (animationEventName == "MoveEnd") {

					MoveEnd();
				}
				else if (animationEventName == "CreateMagic") {

					CreateMagic();
				}
				else if (animationEventName == "InputEnable") {

					InputEnable();
				}
				else {

					std::string errorMsg = "�A�j���[�V�����C�x���g���������Ă΂�Ă��܂���B : ";
					errorMsg += animationEventName;

					nsGameWindow::MessageBoxWarning(nsUtils::GetWideStringFromString(errorMsg).c_str());
				}
			}
		}
	}
}