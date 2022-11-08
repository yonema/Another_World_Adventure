#pragma once

namespace nsAWA {

	namespace nsCamera {

		//���C���J�����N���X
		class CMainCamera : public IGameObject
		{
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		private:
			CVector3 m_position = CVector3::Zero();			//���_
			CVector3 m_target = CVector3::Zero();			//�����_
			CVector3 m_addCameraVec = CVector3::Zero();		//�����_���王�_�܂ł̉��Z�x�N�g��
		};
	}
}

