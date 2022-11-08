#include "YonemaEnginePreCompile.h"
#include "MainCamera.h"

namespace nsAWA {

	namespace nsCamera {

		namespace {

			const CVector3 kStartAddCameraVec = { 0.0f,-200.0f,150.0f };	//開始時点での加算ベクトル
			constexpr const float kCameraFar = 10000.0f;		//どれだけ遠くまでみえるか
			constexpr const float kCameraNear = 1.0f;			//どれだけ近くからみえるか
		}

		bool CMainCamera::Start() {

			MainCamera()->SetFarClip(kCameraFar);
			MainCamera()->SetNearClip(kCameraNear);

			return true;
		}

		void CMainCamera::OnDestroy() {


		}

		void CMainCamera::Update(float deltaTime) {


		}
	}
}
