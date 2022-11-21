#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "Player.h"
#include "../StatusChanger/HealFeature.h"
#include "../StatusChanger/ApplyDamageFeature.h"
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

				//���U���B
				m_playerAction->StrongAttack();
			}

			//�K�[�h�������́B
			if (Input()->IsPress(EnActionMapping::enGuardPreparation)) {

				//�K�[�h���́B
				if (Input()->IsPress(EnActionMapping::enGuard)) {

					//�K�[�h�B
					m_playerAction->Guard();
				}
			}
#ifdef _DEBUG

			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
			//�T���v�����́B
			if (Input()->IsTrigger(EnActionMapping::enStrongAttack)) {

				//�v���C���[��HP���񕜂���B
				nsFeature::HealFeature damage;
				damage.Init(
					player,
					nsFeature::EnHealTarget::enHP,
					100
				);

				//�����B
				damage.Create();
			}

			//�T���v�����́B
			if (Input()->IsTrigger(EnActionMapping::enWeakAttack)) {

				//�v���C���[�Ƀ_���[�W��^����B�i�l�͂��ׂĉ��j
				nsFeature::CApplyDamageFeature damage;
				damage.Init(
					10,			//���x��
					10,			//�З�
					7,			//�U����
					100,		//�h���
					player,		//�^�[�Q�b�g
					false		//�K�[�h�ł���H
				);
				//�����B
				damage.Create();
			}

			if (player != nullptr) {

				//�v���C���[��HP���Q�Ƃ��ăX�v���C�g�ɔ��f�B
				auto sp = FindGO<CSpriteRenderer>("sampleSprite");
				if (sp != nullptr) {

					float hp = static_cast<float>(player->GetStatus()->GetHP());

					hp = hp / 200.0f;
					sp->SetScale({ hp ,hp ,hp });
				}
			}
#endif
		}

		void CPlayerInput::InputSkillAction() {

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_1)) {

#ifdef _DEBUG
				//�f�o�b�O�p�ɃT���v���X�v���C�g�𐶐��B
				if (FindGO<CSpriteRenderer>("sampleSprite") == nullptr) {
					SSpriteInitData sampleSpriteData;
					sampleSpriteData.filePath = "Assets/Images/200x200PNG.png";
					sampleSpriteData.spriteSize = { 300.0f,300.0f };
					auto sampleSprite = NewGO<CSpriteRenderer>("sampleSprite");
					sampleSprite->Init(sampleSpriteData);
					sampleSprite->SetScale(1.0f);
				}
#endif
				//�X�L���P�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_2)) {

				//�X�L���Q�g�p�B
			}

			if (Input()->IsTrigger(EnActionMapping::enUseSkill_3)) {

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