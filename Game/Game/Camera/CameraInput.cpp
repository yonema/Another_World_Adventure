#include "YonemaEnginePreCompile.h"
#include "CameraInput.h"
#include "CameraAction.h"

namespace nsAWA {

	namespace nsCamera {

		namespace {

			constexpr const float kCanPlayerRotateInput = 0.01f;	//��]���͂����肳���Œ�l
		}

		void CCameraInput::Init(CCameraAction* cameraAction) {

			//�J�����A�N�V�����N���X�̃|�C���^���󂯎��B
			m_action = cameraAction;
		}

		void CCameraInput::Update() {

			//�v���C���[���͂ɂ���]�B
			{
				//���͏����󂯎��B
				float cameraRotateInputRight = Input()->GetVirtualAxis(EnAxisMapping::enCameraRight);
				float cameraRotateInputUp = Input()->GetVirtualAxis(EnAxisMapping::enCameraUp);

				//���͂�����Ă��邩�B
				if (std::fabsf(cameraRotateInputRight) > kCanPlayerRotateInput
					|| std::fabsf(cameraRotateInputUp) > kCanPlayerRotateInput
					) {

					//��]�B
					m_action->Rotate(cameraRotateInputUp, cameraRotateInputRight);
				}
			}
		}
	}
}