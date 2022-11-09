#pragma once
#include "CameraInput.h"
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		//メインカメラクラス
		class CMainCamera : public IGameObject
		{
		public:
			static const char* const m_kObjName_MainCamera;		//メインカメラクラスの名前
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
			CCameraInput m_input;		//カメラへの入力
			CCameraAction m_action;		//カメラアクション
		};
	}
}

