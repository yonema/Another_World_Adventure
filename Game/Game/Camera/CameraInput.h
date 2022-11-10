#pragma once
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		//�J�����̓��̓N���X�i��]�⃍�b�N�I���Ȃǂ������\��j
		class CCameraInput : nsUtils::SNoncopyable
		{
		public:

			void Init(CCameraAction* cameraAction);

			void Update();
		private:
			CCameraAction* m_action = nullptr;	//�J�����A�N�V�����N���X�̃|�C���^
		};
	}
}

