#pragma once

namespace nsAWA {

	//�G�C���A�X�錾
	namespace nsCamera {

		class CCameraAction;
	}

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

