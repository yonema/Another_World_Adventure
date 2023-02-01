#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "../Player/Player.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Feature/ApplyDamageFeature.h"
#include "../Feature/HealFeature.h"
#include "../Skill/PassiveSkill.h"
#include "../Skill/PassiveSkillManager.h"
#include "../Skill/ActiveSkill.h"
#include "../Item/SelfItem.h"
#include "../Item/ThrowItem.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Item/ItemManager.h"
#include "../CSV/CSVManager.h"
#include "PlayerManager.h"
#endif

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kCanPlayerMoveInput = 0.001f;	//�ړ����͂����肳���Œ�l
		}

		void CPlayerInput::Init(CPlayerAction* playerAction, nsPlayerAnimation::CPlayerAnimation* playerAnimation) {

			//���͂ɂ���čs�������邽�߁A�v���C���[�A�N�V�����N���X�̃|�C���^���󂯎��B
			m_playerAction = playerAction;

			//�X�e�[�g��ω�������ƂƂ��ɃA�j���[�V�������Đ����邽�߁A�v���C���[�A�j���[�V�����N���X�̃|�C���^���󂯎��B
			m_playerAnimation = playerAnimation;
		}

		void CPlayerInput::Update(bool isAnimationPlaying) {

			//�N�[���^�C�����Ȃ瑁�����^�[���B
			if (m_isCoolTime) { return; }

			//�ړ��E��]���́B
			{
				//���͂��󂯎��B
				auto inputX = Input()->GetVirtualAxis(EnAxisMapping::enRight);
				auto inputZ = Input()->GetVirtualAxis(EnAxisMapping::enForward);
				
				//���͂�����Ă��邩�B
				if (std::fabsf(inputX) > kCanPlayerMoveInput
					|| std::fabsf(inputZ) > kCanPlayerMoveInput
				)
				{
					//�_�b�V���������͂�����Ă��邩�B
					if (Input()->IsPress(EnActionMapping::enDashPreparation)) {

						//�_�b�V����Ԃɂ���B
						m_playerAction->SetState(EnPlayerState::enRun);
					}
					else {
						//������Ԃɂ���B
						m_playerAction->SetState(EnPlayerState::enWalk);
					}

					//�ړ��B
					m_playerAction->Move(
						inputX,
						inputZ
					);

					//��]�B
					m_playerAction->Rotate();
				}
				//�A�j���[�V�������Đ�����Ă��Ȃ��Ȃ�B
				else{

					//�ҋ@��Ԃɐݒ肵�A���̃t���[���͑ҋ@�A�j���[�V�����������悤�ɂ���B
					m_playerAction->SetState(EnPlayerState::enIdle);
				}
			}

			//�X�L���������́B
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//�e�X�L���g�p�ւ̓��͂���t�B
				InputSkillAction();
			}

			//�A�C�e���I�������B
			if (Input()->IsPress(EnActionMapping::enItemSelectPreparation)
				&& !Input()->IsPress(EnActionMapping::enSkillPreparation)
				) {

				//���̃A�C�e����I�ԁB
				if (Input()->IsTrigger(EnActionMapping::enItemSelectRight)) {

					m_playerAction->AddSelectItemNum();
				}

				//�O�̃A�C�e����I�ԁB
				if (Input()->IsTrigger(EnActionMapping::enItemSelectLeft)) {

					m_playerAction->SubSelectItemNum();
				}
			}

			//�X�L���������͂�����Ă��Ȃ�����
			if (!Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//��U�����́B
				if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {

					//�N�[���^�C����ON�ɂ���B
					CoolTimeOn();

					//��U����Ԃɂ���B
					m_playerAction->SetState(EnPlayerState::enWeakAttack);
				}

				//���U�����́B
				if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

					//�N�[���^�C����ON�ɂ���B
					CoolTimeOn();

					//���U����Ԃɂ���B
					m_playerAction->SetState(EnPlayerState::enStrongAttack);
				}

				//�X�e�b�v���́B
				if (Input()->IsTrigger(EnActionMapping::enStep)
					) {

					//�N�[���^�C����ON�ɂ���B
					CoolTimeOn();

					//�X�e�b�v��Ԃɂ���B
					m_playerAction->SetState(EnPlayerState::enStep);
				}

				//�A�C�e���g�p���́B
				if (Input()->IsTrigger(EnActionMapping::enUseItem)
					&& !Input()->IsPress(EnActionMapping::enItemSelectPreparation)
					&& !Input()->IsPress(EnActionMapping::enSkillPreparation)
					) {

					//�A�C�e�����g�p�B
					m_playerAction->UseItem();
				}
			}

			//�K�[�h�������́B
			if (Input()->IsPress(EnActionMapping::enGuardPreparation)) {

				//�K�[�h���́B
				if (Input()->IsPress(EnActionMapping::enGuard)) {

					//�K�[�h�B
					m_playerAction->Guard();
				}
			}
		}

		void CPlayerInput::InputSkillAction() {

#ifdef _DEBUG
			//�v���C���[��T���B
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);
#endif

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {
#ifdef _DEBUG

				//�A�N�e�B�u�X�L����ݒ�B
				CPlayerManager playerManager;
				if (playerManager.FindPlayer()) {
					std::list<nsSkill::SActiveSkillData> list = playerManager.GetCanUseActiveSkillList();
					playerManager.SetActiveSkill(0, "JumpAttack");
				}

				////�N�[���^�C�����ɐݒ�B
				//CoolTimeOn();
				//
				////�X�L���P�g�p�B
				//m_playerAction->UseActiveSkill(EnActiveSkillListNumber::enActiveSkill_1);

				
#endif 
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				//�X�L���Q�g�p�B
#ifdef _DEBUG
				//�A�N�e�B�u�X�L����ݒ�B
				CPlayerManager playerManager;
				if (playerManager.FindPlayer()) {

					playerManager.SetActiveSkill(0, "SwordAttack");
				}

				////�p�b�V�u�X�L���i��Ⴡj�𐶐��B
				//{
				//	//��჋@�\�𐶐��B
				//	nsFeature::nsStatusChanger::CAbnormalStatus* paralysis = new nsFeature::nsStatusChanger::CAbnormalStatus;
				//	paralysis->Init(
				//		nsFeature::nsStatusChanger::EnAbnormalStatusType::enParalysis,
				//		player,
				//		1
				//	);
				//	//�p�b�V�u�X�L���ɋ@�\��ǉ��B
				//	nsSkill::CPassiveSkill* passiveSkill = new nsSkill::CPassiveSkill;
				//	passiveSkill->AddFeature(paralysis);

				//	//�v���C���[�Ƀp�b�V�u�X�L����ݒ�B
				//	player->GetPassiveSkillManager()->AddPassiveSkill(passiveSkill);
				//}
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

				//�X�L���R�g�p�B

#ifdef _DEBUG
				//�A�C�e���i�Łj�𐶐��B
				{
					//�A�C�e�����������B
					nsItem::CThrowItem* item = NewGO<nsItem::CThrowItem>();

					//�ŋ@�\�𐶐��B
					nsFeature::nsStatusChanger::CAbnormalStatus* poison = new nsFeature::nsStatusChanger::CAbnormalStatus;
					poison->Init(
						nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
						player,
						1
					);

					//�����J�n���W��ݒ�B
					item->SetStartPosition(player->GetPosition());
					item->SetThrowDirection(player->GetForwardDirection());

					//�A�C�e���ɋ@�\��ǉ��B
					//item->AddFeature(poison);

					//�A�C�e����ǉ��B
					//player->GetItemManager()->AddItem(item);
				}
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_4)) {

				//�X�L���S�g�p�B

#ifdef _DEBUG
				//�v���C���[�ɃA�C�e����^����B
				player->GetItemManager()->AddItem("�|�[�V����", 2);
#endif
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_5)) {

				//�X�L���T�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_6)) {

				//�X�L���U�g�p�B
			}
		}

		void CPlayerInput::ChangeState() {

			//�X�e�[�g�󋵂�ύX����B
			m_playerAction->ChangeState();
		}
	}
}