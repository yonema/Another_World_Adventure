#pragma once
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		//カメラの入力クラス（回転やロックオンなどを実装予定）
		class CCameraInput : nsUtils::SNoncopyable
		{
		public:

			void Init(CCameraAction* cameraAction);

			void Update();
		private:
			CCameraAction* m_action = nullptr;	//カメラアクションクラスのポインタ
		};
	}
}

