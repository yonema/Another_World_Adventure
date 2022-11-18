#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsCamera {

		class CMainCamera;
	}
	namespace nsPlayer {

		class CPlayerStatus;
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

		//�v���C���[�A�N�V�����N���X
		class CPlayerAction : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void Update(float deltaTime);

			void Move(float inputX,float inputZ);

			void Rotate();

			void Guard();
#ifdef _DEBUG
			//���U���B�W���u���ƂɈႤ�̂Ō�ŏ����B
			void StrongAttack();
#endif
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

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//���C���J�����̃|�C���^
			CPlayerStatus* m_playerStatus = nullptr;			//�v���C���[�X�e�[�^�X�̃|�C���^
		};
	}
}

