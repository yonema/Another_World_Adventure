#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsCamera {

		class CMainCamera;
	}
	namespace nsPlayer {

		class CPlayerStatus;
	}
	namespace nsSkill {

		class CActiveSkill;
	}

	namespace nsPlayer {

		//�v���C���[�X�e�[�g
		enum class EnPlayerState {								
			enIdle,			//�ҋ@
			enWalk,			//����
			enDash,			//�_�b�V��
			enGuard,		//�K�[�h

			enStateNum		//�X�e�[�g��
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
			void Init();

			void Update(float deltaTime);

			void Move(float inputX,float inputZ);

			void Rotate();

			void Guard();

			void SetActiveSkill(EnActiveSkillListNumber activeSkillNum, nsSkill::CActiveSkill* activeSkill);

			void UseActiveSkill(EnActiveSkillListNumber activeSkillNum);
		private:
			const CVector3 CalculateMoveAmount(float inputX, float inputZ);

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
			
			void SetState(const EnPlayerState& state) {

				m_state = state;
			}
			const EnPlayerState& GetState()const {

				return m_state;
			}
		private:
			CVector3 m_position = CVector3::Zero();				//���W
			CQuaternion m_rotation = CQuaternion::Identity();	//��]
			CVector3 m_forwardDirection = CVector3::Zero();		//�O����
			CVector3 m_moveDirection = CVector3::Zero();		//�ړ�����
			EnPlayerState m_state = EnPlayerState::enIdle;		//�X�e�[�g
			float m_deltaTimeRef = 0.0f;						//���̃t���[����deltaTime
			float m_healMPTimer = 0.0f;							//MP�����񕜗p�^�C�}�[
			float m_healSPTimer = 0.0f;							//SP�����񕜗p�^�C�}�[
			float m_healGuardGaugeValueTimer = 0.0f;			//�K�[�h�Q�[�W�̒l�����񕜗p�^�C�}�[
			float m_dashSPTimer = 0.0f;							//�_�b�V���ɂ��SP�_���[�W�^�C�}�[
			nsSkill::CActiveSkill* m_activeSkill[static_cast<int>(EnActiveSkillListNumber::enActiveSkill_Num)] = { nullptr };	//�A�N�e�B�u�X�L��

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//���C���J�����̃|�C���^
			CPlayerStatus* m_playerStatus = nullptr;			//�v���C���[�X�e�[�^�X�̃|�C���^
		};
	}
}

