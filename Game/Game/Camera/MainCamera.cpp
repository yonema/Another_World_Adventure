#include "YonemaEnginePreCompile.h"
#include "MainCamera.h"

namespace nsAWA {

	namespace nsCamera {

		namespace {

			const CVector3 kStartAddCameraVec = { 0.0f,-200.0f,150.0f };	//�J�n���_�ł̉��Z�x�N�g��
			constexpr const float kCameraFar = 10000.0f;		//�ǂꂾ�������܂ł݂��邩
			constexpr const float kCameraNear = 1.0f;			//�ǂꂾ���߂�����݂��邩
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
