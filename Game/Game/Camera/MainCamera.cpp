#include "YonemaEnginePreCompile.h"
#include "MainCamera.h"

namespace nsAWA {

	namespace nsCamera {

		const char* const CMainCamera::m_kObjName_MainCamera = "MainCamera";

		namespace {

			constexpr const float kCameraFar = 10000.0f;		//どれだけ遠くまでみえるか
			constexpr const float kCameraNear = 1.0f;			//どれだけ近くからみえるか
		}

		bool CMainCamera::Start() {

			//カメラに映る範囲を設定。
			MainCamera()->SetFarClip(kCameraFar);
			MainCamera()->SetNearClip(kCameraNear);

			//カメラ入力クラスを初期化。
			m_input.Init(&m_action);

			//カメラアクションクラスを初期化。
			m_action.Init();

			return true;
		}

		void CMainCamera::OnDestroy() {


		}

		void CMainCamera::Update(float deltaTime) {

			//カメラインプットクラスを更新。
			m_input.Update();

			//カメラアクションクラスを更新。
			m_action.Update();

			//注視点を設定。
			MainCamera()->SetTargetPosition(m_action.GetTargetPosition());

			//視点を設定。
			MainCamera()->SetPosition(m_action.GetPosition());

			//更新。
			MainCamera()->UpdateCameraParam();
		}
	}
}
