#pragma once
#include "CameraInput.h"
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		//���C���J�����N���X
		class CMainCamera : public IGameObject
		{
		public:
			static const char* const m_kObjName_MainCamera;		//���C���J�����N���X�̖��O
		private:
			bool Start()override final;

			void OnDestroy()override final;

			void Update(float deltaTime)override final;

		public:

			const CVector3& GetPosition()const {

				return m_action.GetPosition();
			}

			const CVector3& GetTargetPosition()const {

				return m_action.GetTargetPosition();
			}
		private:
			CCameraInput m_input;		//�J�����ւ̓���
			CCameraAction m_action;		//�J�����A�N�V����
		};
	}
}

