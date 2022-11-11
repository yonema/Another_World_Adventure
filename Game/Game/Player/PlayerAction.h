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

		//�v���C���[�A�N�V�����N���X
		class CPlayerAction : nsUtils::SNoncopyable
		{
		public:
			void Init();

			void Update(float deltaTime);

			void Move(float inputX,float inputZ);

			void Rotate();
#ifdef _DEBUG
			void UseSkill(int decreaseMPValue);	//Job���ƂɃX�L���̒����Ⴄ�̂Ō�ŏ����B
#endif
		private:
			const CVector3& CalculateMoveAmount(float inputX, float inputZ);

			void UpdateDeltaTime(float deltaTime) {

				//deltaTime���X�V�B
				m_deltaTimeRef = deltaTime;
			}

			void UpdateForwardDirection();

			void AutoHealMP();
		public:
			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_position;
			}

			const CQuaternion& GetRotation()const {

				return m_rotation;
			}
		private:
			CVector3 m_position = CVector3::Zero();				//���W
			CQuaternion m_rotation = CQuaternion::Identity();	//��]
			CVector3 m_forwardDirection = CVector3::Zero();		//�O����
			CVector3 m_moveDirection = CVector3::Zero();		//�ړ�����
			float m_deltaTimeRef = 0.0f;						//���̃t���[����deltaTime
			float m_healMPTimer = 0.0f;							//HP�����񕜗p�^�C�}�[

			nsCamera::CMainCamera* m_mainCamera = nullptr;		//���C���J�����̃|�C���^
			CPlayerStatus* m_playerStatus = nullptr;			//�v���C���[�X�e�[�^�X�̃|�C���^
		};
	}
}

