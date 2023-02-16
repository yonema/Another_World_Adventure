#pragma once

namespace nsAWA {

	//�O���錾
	namespace nsPlayer {

		class CPlayer;
	}

	namespace nsCamera {

		//�J�����A�N�V�����N���X
		class CCameraAction : nsUtils::SNoncopyable
		{
		private:
			static CVector3 m_startAddCameraVec;		//�J�n���_�ł̉��Z�x�N�g��

		public:
			void Init(nsPlayer::CPlayer* player);

			void Update();

			void Rotate(float rotateUp, float rotateRight);
		public:

			const CVector3& GetPosition()const {

				return m_position;
			}

			const CVector3& GetTargetPosition()const {
				
				return m_targetPosition;
			}

			static inline void SetStartAddCameraVec(const CVector3& vec) noexcept
			{
				m_startAddCameraVec = vec;
			}

			static inline const CVector3& GetStartAddCameraVec() noexcept
			{
				return m_startAddCameraVec;
			}

		private:
			nsPlayer::CPlayer* m_player = nullptr;			//�v���C���[
			CVector3 m_position = CVector3::Zero();			//���_
			CVector3 m_targetPosition = CVector3::Zero();	//�����_
			CVector3 m_addCameraVec = CVector3::Zero();		//�����_���王�_�܂ł̉��Z�x�N�g��
		};
	}
}

