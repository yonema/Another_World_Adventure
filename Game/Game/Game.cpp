#include "YonemaEnginePreCompile.h"
#include "Game.h"
#include "../YonemaEngine.h"
#include "Player/Player.h"
#include "Camera/MainCamera.h"

namespace nsAWA
{
	const char* const CGame::m_kGameObjectName = "Game";

	bool CGame::Start()
	{
		//プレイヤーを生成。
		m_player = NewGO<nsPlayer::CPlayer>(nsPlayer::CPlayer::m_kObjName_Player);

		//メインカメラを生成。
		m_mainCamera = NewGO<nsCamera::CMainCamera>(nsCamera::CMainCamera::m_kObjName_MainCamera);

		//プレイヤーモデルを生成。
		auto modelRenderer = NewGO<CModelRenderer>();

		//ダミーのモデルを配置。（Debug用）
		{
			//プレイヤーモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = "Assets/Models/hoge.fbx";
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);

			//プレイヤーモデルを初期化。
			modelRenderer->Init(modelInitData);
			modelRenderer->SetScale(10.0f);
		}

		return true;
	}

	void CGame::Update(float deltaTime)
	{
		
	}

	void CGame::OnDestroy()
	{
		//プレイヤーを破棄。
		DeleteGO(m_player);

		//メインカメラを破棄。
		DeleteGO(m_mainCamera);
	}


}
