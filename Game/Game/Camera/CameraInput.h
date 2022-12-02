#pragma once

namespace nsAWA {

	//前方宣言
	namespace nsCamera {

		class CCameraAction;
	}

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

