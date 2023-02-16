#include "YonemaEnginePreCompile.h"
#include "PlayerAnimationEvent.h"
#include "../../GameActor.h"
#include "../PlayerInput.h"
#include "../PlayerAction.h"
#include "PlayerAnimation.h"
#include "../../CreateTrigger.h"
#include "../../Skill/ActiveSkill.h"
#include "../../Skill/ActiveSkillList.h"
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

			void CPlayerAnimationEvent::CreateTrigger(const std::string& triggerIndexStr) {

				std::list<std::vector<std::string>> triggerMaterialStr;

				//�X�L���g�p���Ȃ�A���̃X�L���̃A�j���[�V�����C�x���g�f�[�^���擾�B
				if (m_playerAction->GetState() == EnPlayerState::enUseActiveSkill) {

					nsSkill::CActiveSkill* activeSkill = m_playerAnimation->GetReserveActiveSkillInfo();

					nsSkill::CActiveSkill::SActiveSkillAnimData activeSkillAnimData = activeSkill->GetActiveSkillAnimData(triggerIndexStr);
					triggerMaterialStr = activeSkillAnimData.sAnimEventData;
				}
				else {

					//�ʏ�U���B
					std::string attackName = "NoName";

					//���݂̃X�e�[�g���當������擾�B
					switch (m_playerAction->GetState()) {

					case EnPlayerState::enWeakAttack_A:
						attackName = "WeakAttack_A";
						break;
					case EnPlayerState::enWeakAttack_B:
						attackName = "WeakAttack_B";
						break;
					case EnPlayerState::enWeakAttack_C:
						attackName = "WeakAttack_C";
						break;
					case EnPlayerState::enStrongAttack:
						attackName = "StrongAttack";
						break;
					default:
						break;
					}

					//�ʏ�U���̃A�j���[�V�����C�x���g�f�[�^���擾�B
					nsSkill::SActiveSkillData attack = nsSkill::CActiveSkillList::GetInstance()->GetActiveSkillData(attackName);

					for (const auto& data : attack.animDataList) {

						if (data.index == triggerIndexStr) {

							//�ݒ�B
							triggerMaterialStr = data.sAnimEventData;
						}
					}
				}

				//�g���K�[�𐶐��B
				auto trigger = NewGO<CCreateTrigger>();
				trigger->Create(
					m_player,
					triggerMaterialStr,
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

					//�v���C���[�̑O�������擾�B
					const auto& playerDir = m_player->GetForwardDirection();

					//�J�����̑O�������擾�B
					const auto& camDir = MainCamera()->GetForwardDirection();

					//��]��K�p�B
					CQuaternion rot;
					rot.SetRotation(camDir, playerDir);
					m_playerMoveInput = CVector3::Front();
					rot.Apply(m_playerMoveInput);
					m_playerMoveInput.Normalize();
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

			void CPlayerAnimationEvent::GetAnimationEvent(const std::string& animationEventName, const std::string& detailStr) {

				//�C�x���g�̖��O����Ή����郁���o�֐����Ăяo���B

				if (animationEventName == "CoolTimeOn") {

					CoolTimeOn();
				}
				else if (animationEventName == "CoolTimeOff") {

					CoolTimeOff();
				}
				else if (animationEventName == "CreateTrigger") {

					CreateTrigger(detailStr);
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