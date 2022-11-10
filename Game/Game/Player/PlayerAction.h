#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsCamera {

		class CMainCamera;
	}

	namespace nsPlayer {

		//�v���C���[�A�N�V�����N���X
		class CPlayerAction
		{
		public:
			void Init();

			void Move(float inputX,float inputZ);

		public:
			void UpdateDeltaTime(float deltaTime) {

				//deltaTime���X�V�B
				m_deltaTimeRef = deltaTime;
			}

			const CVector3& GetPosition()const {

				//���W���擾�B
				return m_position;
			}
		private:
			CVector3 m_position = CVector3::Zero();	//���W
			float m_deltaTimeRef = 0.0f;			//���̃t���[����deltaTime	
			nsCamera::CMainCamera* m_mainCamera = nullptr;		//���C���J�����̃|�C���^
		};
	}
}

