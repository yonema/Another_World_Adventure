#pragma once
#include "CameraInput.h"
#include "CameraAction.h"

namespace nsAWA {

	namespace nsPlayer {

		class CPlayer;
	}

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

			const CVector3& GetForwardDirection()const {

				//前方向を取得。
				return MainCamera()->GetForwardDirection();
			}

			const CVector3& GetRightDirection()const {

				//右方向を取得。
				return MainCamera()->GetRightDirection();
			}
		private:
			CCameraInput m_input;		//カメラへの入力
			CCameraAction m_action;		//カメラアクション
		};
	}
}

