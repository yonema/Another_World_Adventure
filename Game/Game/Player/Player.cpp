#include "YonemaEnginePreCompile.h"
#include "Player.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/hoge.fbx";	//�v���C���[���f���̃t�@�C���p�X
	}

	namespace nsPlayer {

		bool CPlayer::Start() {

			//�v���C���[���f���𐶐��B
			CreatePlayerModel();

			return true;
		}

		void CPlayer::OnDestroy() {

			//�v���C���[���f����j���B
			DeleteGO(m_modelRenderer);
		}

		void CPlayer::Update(float deltaTime) {


		}

		void CPlayer::CreatePlayerModel() {

			//�v���C���[���f���𐶐��B
			m_modelRenderer = NewGO<CModelRenderer>();

			//�v���C���[���f���̏������f�[�^���`�B
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//�v���C���[���f�����������B
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(10.0f);
		}
	}
}

