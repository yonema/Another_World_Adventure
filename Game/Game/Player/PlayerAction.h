#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsCamera {

		class CMainCamera;
	}
	namespace nsPlayer {

		class CPlayerStatus;

		namespace nsPlayerAnimation {

			class CPlayerAnimation;
		}
	}
	namespace nsSkill {

		class CActiveSkill;
	}
	namespace nsItem {

		class CItemManager;
	}
	namespace nsFeature {

		class CFeatureManager;
	}

	namespace nsPlayer {

		//�v���C���[�X�e�[�g
		enum class EnPlayerState {								
			enIdle,			//�ҋ@
			enWalk,			//����
			enRun,			//�_�b�V��
			enWeakAttack,	//��U��
			enStrongAttack,	//���U��
			enStep,			//�X�e�b�v
			enUseActiveSkill,//�A�N�e�B�u�X�L��
			enDamage,		//��e
			enDeath,		//���S
			enGuard,		//�K�[�h
			enUseItem,		//�A�C�e���g�p
			enStun,			//�X�^��

			enStateNum,		//�X�e�[�g��
			enNone			//�ݒ�Ȃ�
		};

		//�A�N�e�B�u�X�L���̔ԍ�
		enum class EnActiveSkillListNumber {

			enActiveSkill_1,	//�X�L��1
			enActiveSkill_2,	//�X�L��2
			enActiveSkill_3,	//�X�L��3
			enActiveSkill_4,	//�X�L��4
			enActiveSkill_5,	//�X�L��5
			enActiveSkill_6,	//�X�L��6

			enActiveSkill_Num,	//���蓖�Ă���A�N�e�B�u�X�L����
		};

		//�v���C���[�A�N�V�����N���X
		class CPlayerAction : nsUtils::SNoncopyable
		{
		public:
			void Init(
				CPlayerStatus* playerStatus, 
				nsItem::CItemManager* playerItemManager,
				nsFeature::CFeatureManager* playerFeatureManager,
				nsPlayerAnimation::CPlayerAnimation* playerAnimation
			);

			void Update(float deltaTime);

			void Move(float inputX,float inputZ, float speed = 0.0f);

			void Rotate(bool slerp = true);

			void Guard();

			void UseItem();

			void AddSelectItemNum();

			void SubSelectItemNum();

			void SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill);

			void UseActiveSkill(EnActiveSkillListNumber activeSkillNum);
		private:
			const CVector3 CalculateMoveAmount(float inputX, float inputZ, float speed);

			void UpdateDeltaTime(float deltaTime) {

				//deltaTime���X�V�B
				m_deltaTimeRef = deltaTime;
			}

			void UpdateForwardDirection();

			void AutoHealMP();

			void AutoHealSP();

			void DamageSPDash();

			void AutoHealGuardGaugeValue();
		public:
			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_position;
			}

			const CQuaternion& GetRotation()const {

				return m_rotation;
			}

			const CVector3& GetForwardDirection()const {

				return m_forwardDirection;
			}
			
			void SetState(const EnPlayerState& state) {

				//�X�e�[�g���ς������B
				if (m_state != state) {

					//�V�����X�e�[�g��ݒ肷��B
					m_state = state;

					//�X�e�[�g�ɕύX���������B
					m_isChangeState = true;
				}
			}

			void ResetChangeState() {

				//�X�e�[�g�̕ύX�󋵂��������B
				m_isChangeState = false;
			}

			void ChangeState() {

				//�X�e�[�g������������B
				m_state = EnPlayerState::enNone;
				m_isChangeState = true;
			}

			const EnPlayerState& GetState()const {

				return m_state;
			}

			bool IsChangeState()const {

				return m_isChangeState;
			}
		private:
			CVector3 m_position = CVector3::Zero();				//���W
			CQuaternion m_rotation = CQuaternion::Identity();	//��]
			CVector3 m_forwardDirection = CVector3::Zero();		//�O����
			CVector3 m_moveDirection = CVector3::Zero();		//�ړ�����
			bool m_isChangeState = false;						//�X�e�[�g�����̃t���[���ŕύX���ꂽ�H
			EnPlayerState m_state = EnPlayerState::enNone;		//�X�e�[�g
			float m_deltaTimeRef = 0.0f;						//���̃t���[����deltaTime
			nsSkill::CActiveSkill* m_activeSkill[static_cast<int>(EnActiveSkillListNumber::enActiveSkill_Num)] = { nullptr };	//�A�N�e�B�u�X�L��

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//���C���J�����̃|�C���^
			CPlayerStatus* m_playerStatus = nullptr;			//�v���C���[�X�e�[�^�X�̃|�C���^
			nsPlayerAnimation::CPlayerAnimation* m_playerAnimation = nullptr;		//�v���C���[�A�j���[�V����
			nsItem::CItemManager* m_playerItemManager = nullptr;//�v���C���[�̃A�C�e���Ǘ��N���X�̃|�C���^
			nsFeature::CFeatureManager* m_playerFeatureManager = nullptr;	//�v���C���[�̃X�e�[�^�X�ω��Ǘ��N���X�̃|�C���^
		};
	}
}

