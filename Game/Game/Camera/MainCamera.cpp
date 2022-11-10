#include "YonemaEnginePreCompile.h"
#include "MainCamera.h"

namespace nsAWA {

	namespace nsCamera {

		const char* const CMainCamera::m_kObjName_MainCamera = "MainCamera";

		namespace {

			constexpr const float kCameraFar = 10000.0f;		//�ǂꂾ�������܂ł݂��邩
			constexpr const float kCameraNear = 1.0f;			//�ǂꂾ���߂�����݂��邩
		}

		bool CMainCamera::Start() {

			//�J�����ɉf��͈͂�ݒ�B
			MainCamera()->SetFarClip(kCameraFar);
			MainCamera()->SetNearClip(kCameraNear);

			//�J�������̓N���X���������B
			m_input.Init(&m_action);

			//�J�����A�N�V�����N���X���������B
			m_action.Init();

			return true;
		}

		void CMainCamera::OnDestroy() {


		}

		void CMainCamera::Update(float deltaTime) {

			//�J�����C���v�b�g�N���X���X�V�B
			m_input.Update();

			//�J�����A�N�V�����N���X���X�V�B
			m_action.Update();

			//�����_��ݒ�B
			MainCamera()->SetTargetPosition(m_action.GetTargetPosition());

			//���_��ݒ�B
			MainCamera()->SetPosition(m_action.GetPosition());

			//�X�V�B
			MainCamera()->UpdateCameraParam();
		}
	}
}
