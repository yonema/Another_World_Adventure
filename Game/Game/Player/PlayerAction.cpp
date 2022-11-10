#include "YonemaEnginePreCompile.h"
#include "PlayerAction.h"
#include "../Camera/MainCamera.h"

namespace nsAWA {

	namespace nsPlayer {

		namespace {

			constexpr const float kMoveAmount = 20.0f;		//移動量
		}

		void CPlayerAction::Move(float inputX, float inputZ) {
			
			//カメラを検索。
			auto camera = FindGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

			//カメラの前方向、右方向を取得。
			auto cameraForward = camera->GetForwardDirection();
			auto cameraRight = camera->GetRightDirection();

			//不要な成分を初期化して正規化。
			cameraForward.y = 0.0f;
			cameraForward.Normalize();
			cameraRight.y = 0.0f;
			cameraRight.Normalize();

			//移動量を計算。
			CVector3 moveAmount = CVector3::Zero();
			moveAmount += cameraForward * inputZ * kMoveAmount * m_deltaTimeRef;
			moveAmount += cameraRight * inputX * kMoveAmount * m_deltaTimeRef;

			//移動。
			m_position += moveAmount;
		}
	}
}
