#include "YonemaEnginePreCompile.h"
#include "Player.h"

namespace nsAWA {

	namespace {

		constexpr const char* const kPlayerModelFilePath = "Assets/Models/hoge.fbx";	//プレイヤーモデルのファイルパス
	}

	namespace nsPlayer {

		const char* const CPlayer::m_kObjName_Player = "Player";

		bool CPlayer::Start() {

			//プレイヤーモデルを生成。
			CreatePlayerModel();

			//入力クラスを初期化。
			m_input.Init(&m_action);

			//アクションクラスを初期化。
			m_action.Init();

			return true;
		}

		void CPlayer::OnDestroy() {

			//プレイヤーモデルを破棄。
			DeleteGO(m_modelRenderer);
		}

		void CPlayer::Update(float deltaTime) {

			//プレイヤーアクションクラスのdeltaTimeを更新（Updateではなく各関数で必要になるため）。
			m_action.UpdateDeltaTime(deltaTime);

			//入力クラスを更新。
			m_input.Update();

			//座標を設定。
			m_modelRenderer->SetPosition(m_action.GetPosition());
		}

		void CPlayer::CreatePlayerModel() {

			//プレイヤーモデルを生成。
			m_modelRenderer = NewGO<CModelRenderer>();

			//プレイヤーモデルの初期化データを定義。
			SModelInitData modelInitData;
			modelInitData.modelFilePath = kPlayerModelFilePath;
			modelInitData.modelFormat = nsGraphics::nsRenderers::EnModelFormat::enFBX;
			modelInitData.vertexBias.SetRotationX(nsMath::YM_PIDIV2);
			modelInitData.vertexBias.AddRotationY(nsMath::YM_PI);

			//プレイヤーモデルを初期化。
			m_modelRenderer->Init(modelInitData);
			m_modelRenderer->SetScale(10.0f);
		}
	}
}

