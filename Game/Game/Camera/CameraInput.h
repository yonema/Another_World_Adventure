#pragma once
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		//カメラの入力クラス（回転やロックオンなどを実装予定）
		class CCameraInput
		{
		public:

			void Init(CCameraAction* cameraAction);

			void Update();
		private:
			CCameraAction* m_action = nullptr;	//カメラアクションクラスのポインタ
		};
	}
}

