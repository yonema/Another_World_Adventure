#include "YonemaEnginePreCompile.h"
#include "CameraInput.h"
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		namespace {

			constexpr const float kCanPlayerRotateInput = 0.01f;	//回転入力が判定される最低値
		}

		void CCameraInput::Init(CCameraAction* cameraAction) {

			//カメラアクションクラスのポインタを受け取る。
			m_action = cameraAction;
		}

		void CCameraInput::Update() {

			//プレイヤー入力による回転。
			{
				//入力情報を受け取る。
				float cameraRotateInputRight = Input()->GetVirtualAxis(EnAxisMapping::enCameraRight);
				float cameraRotateInputUp = Input()->GetVirtualAxis(EnAxisMapping::enCameraUp);

				//入力がされているか。
				if (std::fabsf(cameraRotateInputRight) > kCanPlayerRotateInput
					|| std::fabsf(cameraRotateInputUp) > kCanPlayerRotateInput
					) {

					//回転。
					m_action->Rotate(cameraRotateInputUp, cameraRotateInputRight);
				}
			}
		}
	}
}