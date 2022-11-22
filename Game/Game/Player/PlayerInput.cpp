#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "../Player/Player.h"
#include "../Feature/AbnormalStatus/Poison.h"
#include "../Feature/ApplyDamageFeature.h"
#include "../Feature/HealFeature.h"
#endif

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kCanPlayerMoveInput = 0.001f;	//�ړ����͂����肳���Œ�l
		}

		void CPlayerInput::Init(CPlayerAction* playerAction) {

			//���͂ɂ���čs�������邽�߁A�v���C���[�A�N�V�����N���X�̃|�C���^���󂯎��B
			m_playerAction = playerAction;
		}

		void CPlayerInput::Update() {

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
						m_playerAction->SetState(EnPlayerState::enDash);
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
				else {

					//�ҋ@��Ԃɐݒ肷��B
					m_playerAction->SetState(EnPlayerState::enIdle);
				}
			}

			//�X�L���������́B
			if (Input()->IsPress(EnActionMapping::enSkillPreparation)) {

				//�e�X�L���g�p�ւ̓��͂���t�B
				InputSkillAction();
			}

			//���U�����́B
			if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

				
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
			//�v���C��[��T���B
			auto player = FindGO<CPlayer>(CPlayer::m_kObjName_Player);
#endif

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {
#ifdef _DEBUG
				//�_���[�W�B
				nsFeature::CApplyDamageFeature damage;
				damage.Init(
					12,			//���x��
					10,			//�З�
					20,			//�U����
					14,			//�h���
					player,		//�^�[�Q�b�g
					false		//�K�[�h�ł���H
					);
				damage.Create();
#endif 
				//�X�L���P�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {
#ifdef _DEBUG
				//�񕜁B
				nsFeature::HealFeature heal;
				heal.Init(player, nsFeature::EnHealTarget::enHP, 100);
				heal.Create();
#endif

				//�X�L���Q�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {
#ifdef _DEBUG
				//�ŁB
				nsFeature::nsStatusChanger::CAbnormalStatus abnormalStatus;
				abnormalStatus.Init(
					nsFeature::nsStatusChanger::EnAbnormalStatusType::enPoison,
					player,
					1		//���x��
				);
				abnormalStatus.Create();
#endif
				//�X�L���R�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_4)) {

				//�X�L���S�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_5)) {

				//�X�L���T�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_6)) {

				//�X�L���U�g�p�B
			}
		}
	}
}