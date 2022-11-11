#include "YonemaEnginePreCompile.h"
#include "PlayerInput.h"
#include "PlayerAction.h"

#ifdef _DEBUG
#include "Player.h"
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

#ifdef _DEBUG
			//�v���C���[�������B
			auto player = FindGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);
			if (player != nullptr) {

				auto sp = FindGO<CSpriteRenderer>("sampleSprite");
				if (sp != nullptr) {

					float playerSP = static_cast<float>(player->GetStatus()->GetSP());
					playerSP = playerSP / 100.0f;
					sp->SetScale({ playerSP ,playerSP ,playerSP });
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